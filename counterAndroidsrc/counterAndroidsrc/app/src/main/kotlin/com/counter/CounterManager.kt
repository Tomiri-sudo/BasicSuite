package com.counter

import android.content.Context
import androidx.datastore.preferences.core.booleanPreferencesKey
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.core.intPreferencesKey
import androidx.datastore.preferences.preferencesDataStore
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

val Context.dataStore by preferencesDataStore(name = "settings")

class CounterManager(private val context: Context) {
    
    // Define DataStore Keys
    private val COUNT_KEY = intPreferencesKey("count_value")
    private val VIBRATE_KEY = booleanPreferencesKey("vibrate_enabled")
    private val STEP_KEY = intPreferencesKey("step_value")

    // --- READ FLOWS ---
    val getCount: Flow<Int> = context.dataStore.data.map { prefs -> 
        prefs[COUNT_KEY] ?: 0 
    }
    
    val isVibrationEnabled: Flow<Boolean> = context.dataStore.data.map { prefs -> 
        prefs[VIBRATE_KEY] ?: true // Default to true (vibrate on)
    }
    
    val getStepValue: Flow<Int> = context.dataStore.data.map { prefs -> 
        prefs[STEP_KEY] ?: 1 // Default step is 1
    }

    // --- WRITE FUNCTIONS ---
    suspend fun saveCount(value: Int) {
        context.dataStore.edit { prefs -> prefs[COUNT_KEY] = value }
    }

    suspend fun saveVibrationSetting(enabled: Boolean) {
        context.dataStore.edit { prefs -> prefs[VIBRATE_KEY] = enabled }
    }

    suspend fun saveStepValue(value: Int) {
        context.dataStore.edit { prefs -> prefs[STEP_KEY] = value }
    }
}
