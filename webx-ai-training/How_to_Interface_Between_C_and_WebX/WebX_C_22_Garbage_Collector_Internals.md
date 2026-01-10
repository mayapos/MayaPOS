# Chapter 22: WebX (Harbour) Garbage Collector Internals

## Introduction

The WebX (Harbour) Virtual Machine (HBVM) utilizes a sophisticated **Garbage Collector (GC)** to manage memory for complex data types. Unlike simple reference counting, which can fail to reclaim memory in the presence of circular references, the WebX GC employs a **Mark and Sweep** algorithm.

This chapter explores the inner workings of the GC, how it handles different data types, and how C developers should interact with it to ensure system stability.

## The Mark and Sweep Algorithm

The Garbage Collector operates in three distinct phases:

1.  **Mark Phase**: At the start of a collection cycle, the GC marks all memory blocks it manages as "potentially unused."
2.  **Scan Phase**: The GC recursively scans all "life" variables in the VM. This includes:
    *   The Evaluation Stack.
    *   Public and Private memvars.
    *   Static variables.
    *   Local variables of active functions.
    If a reference to a memory block is found during this scan, the block is marked as "used."
3.  **Sweep Phase**: Any memory blocks that remain marked as "potentially unused" (not found during the scan) are released back to the system.

## Target Data Types

The Garbage Collector primarily manages "collectable" items—types that are capable of circular or self-references. These include:

*   **Arrays**: An array can contain an index that points back to itself or to another array that points to it.
*   **Objects**: Objects often have circular references between themselves and their data or methods.
*   **Codeblocks**: Codeblocks can capture their environment, leading to complex reference chains.

Simple types like **Strings**, **Numbers**, and **Booleans** typically manage their lifetime through stack-level scoping or simple reference counting, as they cannot form circular references.

## Interaction with the C-API

When writing C extensions for WebX (Harbour), it is CRITICAL to interact with the GC correctly:

### 1. Allocation: `hb_gcAlloc()`
If you need to allocate memory for a structure that might be stored within a WebX item (like an array element or object data), use `hb_gcAlloc()`. This allows the GC to track the allocation.

```c
void * pMemory = hb_gcAlloc( nSize, hb_gcFreeFunc );
```

### 2. Retention: `hb_itemNew()`
If you store a pointer to a collectable item in a **static C variable**, you MUST use `hb_itemNew()` to create a persistent reference. If you don't, the GC might think the item is no longer in use and reclaim it, leading to a crash when your C code later tries to access it.

### 3. Manual Invocation
While the GC usually runs during **idle states** (e.g., waiting for input in `Inkey()`), it can be manually triggered using:
*   `hb_gcAll()`: Performs a full collection cycle.
*   `hb_gcCollectAll()`: A more aggressive collection.

## Best Practices

*   **Avoid Manual Freeing**: Let the GC handle blocks allocated with `hb_gcAlloc()`.
*   **Use Stack Variables**: When possible, use local stack variables to store items, as these are automatically scanned by the GC.
*   **Document Side Effects**: If your C function triggers a GC cycle, document it, as it may impact performance.

---
*Note: This information is based on the technical research from the Harbour Project and community documentation.*
