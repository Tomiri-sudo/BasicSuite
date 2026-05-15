package com.counter

import android.os.Bundle
import android.content.Context // Added
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.*
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext // Added
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.counter.ui.theme.ComposeEmptyActivityTheme
import kotlinx.coroutines.launch // Added

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ComposeEmptyActivityTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Box(modifier = Modifier.padding(innerPadding)) {
                        PersistentCounter(LocalContext.current)
                    }
                }
            }
        }
    }
}

@Composable
fun PersistentCounter(context: Context) {
    // Initialize our storage manager
    val counterManager = remember { CounterManager(context) }
    
    // Observe the persistent value from DataStore
    val count by counterManager.getCount.collectAsState(initial = 0)
    
    // Create a scope that is tied to this Composable's lifecycle
    val scope = rememberCoroutineScope()

    Column(
        modifier = Modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "$count", fontSize = 32.sp)
        
        Spacer(modifier = Modifier.height(16.dp))

        Button(onClick = { 
            // We use 'scope.launch' to call the suspend function
            scope.launch { 
                counterManager.saveCount(count + 1) 
            } 
        }) {
            Text("+")
        }
        
        //new decrease button
        Button(onClick = { 
            // We use 'scope.launch' to call the suspend function
            scope.launch { 
                counterManager.saveCount(count - 1) 
            } 
        }) {
            Text("-")
        }
        
        Button(
            onClick = { 
                scope.launch { counterManager.saveCount(0) } 
            }, 
            modifier = Modifier.padding(top = 8.dp)
        ) {
            Text("Reset")
        }
    }
}
