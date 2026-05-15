package com.counter

import android.app.Activity
import android.os.Bundle
import android.content.Context
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.selection.selectable
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.hapticfeedback.HapticFeedbackType
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalHapticFeedback
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.counter.ui.theme.ComposeEmptyActivityTheme
import kotlinx.coroutines.launch

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ComposeEmptyActivityTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Box(modifier = Modifier.padding(innerPadding)) {
                        AppNavigation(LocalContext.current)
                    }
                }
            }
        }
    }
}

@Composable
fun AppNavigation(context: Context) {
    // Simple state-based router
    var currentScreen by remember { mutableStateOf("counter") }

    if (currentScreen == "counter") {
        PersistentCounter(
            context = context, 
            onNavigateToSettings = { currentScreen = "settings" }
        )
    } else {
        SettingsScreen(
            context = context, 
            onNavigateBack = { currentScreen = "counter" }
        )
    }
}

@Composable
fun PersistentCounter(context: Context, onNavigateToSettings: () -> Unit) {
    val counterManager = remember { CounterManager(context) }
    
    // Collect all persistent settings
    val count by counterManager.getCount.collectAsState(initial = 0)
    val vibrateEnabled by counterManager.isVibrationEnabled.collectAsState(initial = true)
    val stepValue by counterManager.getStepValue.collectAsState(initial = 1)
    
    val scope = rememberCoroutineScope()
    val haptic = LocalHapticFeedback.current
    val activity = (context as? Activity)

    // Helper helper to trigger haptic feedback conditionally
    val triggerVibration = {
        if (vibrateEnabled) {
            haptic.performHapticFeedback(HapticFeedbackType.LongPress)
        }
    }

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "$count", fontSize = 64.sp)
        Text(text = "Step size: $stepValue", fontSize = 14.sp, color = MaterialTheme.colorScheme.secondary)
        
        Spacer(modifier = Modifier.height(24.dp))

        Button(onClick = { 
            triggerVibration()
            scope.launch { counterManager.saveCount(count + stepValue) } // Uses dynamic step
        }) {
            Text("+ $stepValue", fontSize = 20.sp)
        }
        
        Spacer(modifier = Modifier.height(8.dp))
        
        Button(onClick = { 
            triggerVibration()
            scope.launch { counterManager.saveCount(count - stepValue) } // Uses dynamic step
        }) {
            Text("- $stepValue", fontSize = 20.sp)
        }
        
        Spacer(modifier = Modifier.height(16.dp))
        
        Button(onClick = { 
            triggerVibration()
            scope.launch { counterManager.saveCount(0) } 
        }) {
            Text("Reset")
        }

        Spacer(modifier = Modifier.height(48.dp))

        // Settings Navigation Button
        Button(onClick = { 
            triggerVibration()
            onNavigateToSettings() 
        }) {
            Text("Settings")
        }

        Spacer(modifier = Modifier.height(16.dp))

        Button(
            onClick = { 
                triggerVibration()
                activity?.finish() 
            },
            colors = ButtonDefaults.buttonColors(
                containerColor = MaterialTheme.colorScheme.errorContainer,
                contentColor = MaterialTheme.colorScheme.onErrorContainer
            )
        ) {
            Text("Quit")
        }
    }
}

@Composable
fun SettingsScreen(context: Context, onNavigateBack: () -> Unit) {
    val counterManager = remember { CounterManager(context) }
    
    val vibrateEnabled by counterManager.isVibrationEnabled.collectAsState(initial = true)
    val stepValue by counterManager.getStepValue.collectAsState(initial = 1)
    
    val scope = rememberCoroutineScope()
    val stepsOptions = listOf(1, 2, 5, 10)

    Column(
        modifier = Modifier
            .fillMaxSize()
            .padding(24.dp),
        verticalArrangement = Arrangement.Top,
        horizontalAlignment = Alignment.Start
    ) {
        Text("Settings", fontSize = 32.sp, modifier = Modifier.padding(bottom = 24.dp))

        // 1. VIBRATION TOGGLE ROW
        Row(
            modifier = Modifier.fillMaxWidth(),
            horizontalArrangement = Arrangement.SpaceBetween,
            verticalAlignment = Alignment.CenterVertically
        ) {
            Text("Button Haptic Feedback", fontSize = 18.sp)
            Switch(
                checked = vibrateEnabled,
                onCheckedChange = { newValue ->
                    scope.launch { counterManager.saveVibrationSetting(newValue) }
                    
                }
            )
        }

        Divider(modifier = Modifier.padding(vertical = 24.dp))

        // 2. STEP SELECTION SECTION
        Text("Counter Step Increment", fontSize = 18.sp, modifier = Modifier.padding(bottom = 8.dp))
        
        stepsOptions.forEach { option ->
            Row(
                Modifier
                    .fillMaxWidth()
                    .selectable(
                        selected = (option == stepValue),
                        onClick = {
                            scope.launch { counterManager.saveStepValue(option) }
                        }
                    )
                    .padding(vertical = 12.dp),
                verticalAlignment = Alignment.CenterVertically
            ) {
                RadioButton(
                    selected = (option == stepValue),
                    onClick = { scope.launch { counterManager.saveStepValue(option) } }
                )
                Text(
                    text = "Increase/Decrease by $option",
                    fontSize = 16.sp,
                    modifier = Modifier.padding(start = 16.dp)
                )
            }
        }

        Spacer(modifier = Modifier.weight(1f)) // Pushes back button to bottom

        // 3. BACK BUTTON
        Button(
            onClick = onNavigateBack,
            modifier = Modifier.fillMaxWidth()
        ) {
            Text("Back to Counter")
        }
    }
}
