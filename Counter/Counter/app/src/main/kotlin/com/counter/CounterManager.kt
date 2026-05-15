package com.counter

import android.content.Context
import androidx.datastore.preferences.core.edit
import androidx.datastore.preferences.core.intPreferencesKey
import androidx.datastore.preferences.preferencesDataStore
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

// Extension to get the DataStore instance
val Context.dataStore by preferencesDataStore(name = "settings")

class CounterManager(private val context: Context) {
    private val COUNT_KEY = intPreferencesKey("count_value")

    // Read the count as a Flow (reactive stream)
    val getCount: Flow<Int> = context.dataStore.data
        .map { preferences ->
            preferences[COUNT_KEY] ?: 0 // Default to 0
        }

    // Save the count
    suspend fun saveCount(value: Int) {
        context.dataStore.edit { preferences ->
            preferences[COUNT_KEY] = value
        }
    }
}
