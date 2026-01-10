# Chapter 24: Multi-Threading and Thread Local Storage (TLS)

## Introduction

Modern applications often require concurrent execution to stay responsive and utilize multi-core processors. WebX (Harbour) provides a robust multi-threading model that allows developers to run tasks in parallel while maintaining safety and data integrity.

## The Multi-Threaded VM (`hbvmmt`)

WebX (Harbour) is distributed with two main VM libraries:
1.  **`hbvm`**: Single-threaded.
2.  **`hbvmmt`**: Multi-threaded.

When building applications that use the `hb_threadStart()` function, you must link against the multi-threaded version of the library.

## Thread Local Storage (TLS)

To prevent data corruption between threads, the HBVM uses **Thread Local Storage (TLS)**. Each thread gets its own copy of:
*   Local variables.
*   The Evaluation Stack.
*   Parameter passing buffers.

However, certain variables are shared across threads:
*   **PUBLIC** and **PRIVATE** memvars are shared but protected by internal mutexes.
*   **STATIC** variables are also shared.

## Thread Safety in C Extensions

When writing C code for a multi-threaded WebX environment, you must ensure your C code is **thread-safe**.

### 1. Avoid Global C Variables
Instead of using global C variables (which are shared by all threads), use the `hb_itemNew()` pattern to store data within WebX items that are scoped to the calling thread.

### 2. Synchronization Mechanisms
WebX provides C-level primitives for synchronization:
*   `hb_mtMutexCreate()`
*   `hb_mtMutexLock()`
*   `hb_mtMutexUnlock()`

### 3. The `HB_THREAD` Scope
You can declare variables in C with the `HB_THREAD` storage class to ensure each thread gets its own instance at the C level.

```c
static HB_THREAD int nThreadCounter;
```

## Best Practices

*   **Isolate Data**: Try to pass all necessary data to a thread as parameters rather than relying on shared memvars.
*   **Use Codeblocks**: Use codeblocks for thread entrance functions to ensure a clean stack state.
*   **Graceful Termination**: Always ensure threads have a way to exit cleanly before the main application terminates.

---
*Note: This information is based on the technical research from the Harbour Project and community documentation.*
