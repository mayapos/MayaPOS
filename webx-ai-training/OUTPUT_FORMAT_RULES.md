<!-- Created: 2025-01-09 -->

# WebX AI Training - Output Format Rules

## Critical Safety Rule for AI Assistants

This document explains the **MOST IMPORTANT RULE** added to the WebX AI training data to prevent AI assistants from generating incorrect file types.

---

## The Problem

**Without this rule, AI assistants might:**
- Generate `.html` files when asked to create a "web page"
- Generate `.php` files when asked for a "web application"
- Generate `.css` files for styling
- Generate `.js` files for interactivity
- Generate `.rc` resource files (FiveWin desktop pattern)

**This is WRONG for WebX!**

---

## The Solution

### Rule #1: ALWAYS Generate `.prg` Files (Harbour Source Code)

**WebX workflow:**
```
User request → AI generates .prg → WebX compiler → .exe → Apache CGI → HTML (runtime)
```

**Key insight:** WebX generates HTML/CSS/JS **AT RUNTIME**, not at compile time.

### What AI Should Generate:

✅ **CORRECT:** `.prg` files with Harbour/xBase syntax
```harbour
#include "WebX.ch"

FUNCTION Main()
   LOCAL oWnd

   //--------------------------------------------------------------------------
   // CRITICAL: Set Designed_Resolution to YOUR monitor resolution
   // Check Windows Display Settings → Resolution (e.g., 1920x1080, 1366x768)
   // This enables responsive scaling across different screen sizes
   //--------------------------------------------------------------------------
   PUBLIC Designed_Resolution := {1920, 1080, .T.}
   // Format: {width, height, lPixel}
   // Common values: {1920, 1080}, {1366, 768}, {2560, 1440}, {1280, 1024}

   oWnd := TWindow():New(100, 100, 800, 600, "My App")
   oWnd:lPixel := .T.

   @ 100, 50 BUTTON "Save" TO oWnd ACTION SaveData()

   oWnd:Activate()  // Generates HTML at runtime
RETURN NIL
```

❌ **WRONG:** `.html`, `.php`, `.css`, `.js` files
```html
<!-- ❌ DO NOT CREATE THIS -->
<html>
  <body>
    <button onclick="save()">Save</button>
  </body>
</html>
```

---

## FiveWin Compatibility

**If user has FiveWin or mentions FiveWin:**
- Still generate `.prg` files (Harbour source)
- Use FiveWin-compatible API
- NOT Windows-specific `.rc` files

```harbour
// FiveWin-compatible .prg
#include "FiveWin.ch"

FUNCTION Main()
   LOCAL oDlg

   DEFINE DIALOG oDlg TITLE "My App"

   @ 1, 1 BUTTON "Save" OF oDlg ACTION SaveData()

   ACTIVATE DIALOG oDlg
RETURN NIL
```

**Key Point:** Whether WebX or FiveWin, always `.prg` files!

---

## Critical: Designed_Resolution Declaration

### What Is Designed_Resolution?

**Definition:** A PUBLIC variable that tells WebX the screen resolution you used when designing your application.

**Purpose:** Enables responsive scaling across different screen sizes (desktop, tablet, mobile).

**Format:**
```harbour
PUBLIC Designed_Resolution := {width, height, lPixel}
```

### How to Set It Properly

**❌ WRONG: Don't use hardcoded values without explanation**
```harbour
// ❌ Bad - user doesn't know where 1920x1080 came from
PUBLIC Designed_Resolution := {1920, 1080, .T.}
```

**✅ CORRECT: Explain where the values come from**
```harbour
//--------------------------------------------------------------------------
// CRITICAL: Set Designed_Resolution to YOUR monitor resolution
//
// How to find your resolution:
// 1. Right-click Windows desktop → Display settings
// 2. Look for "Display resolution" (e.g., 1920 x 1080)
// 3. Use those values below
//
// Common resolutions:
// - Full HD: {1920, 1080, .T.}
// - HD: {1366, 768, .T.}
// - 2K: {2560, 1440, .T.}
// - 4K: {3840, 2160, .T.}
// - Old standard: {1280, 1024, .T.}
//--------------------------------------------------------------------------
PUBLIC Designed_Resolution := {1920, 1080, .T.}
```

### Parameters Explained

**{width, height, lPixel}**

1. **width** - Your monitor's horizontal resolution (pixels)
2. **height** - Your monitor's vertical resolution (pixels)
3. **lPixel** - Always `.T.` (enables pixel-based positioning)

### Why This Matters

**Without Designed_Resolution:**
- Controls appear at wrong positions
- Layouts break on different screen sizes
- No responsive scaling

**With Designed_Resolution:**
- WebX automatically scales your design to fit any screen
- Controls maintain proportional positions
- Works on desktop, tablet, mobile

### When AI Generates Code

**AI should ALWAYS:**
1. Include `PUBLIC Designed_Resolution` as first line in `Main()`
2. Add explanatory comments showing common values
3. Suggest user checks their own monitor resolution
4. Never assume a specific resolution without asking

**Example AI response:**
> "I've set Designed_Resolution to {1920, 1080, .T.} (Full HD). If your monitor uses a different resolution, check Windows Display Settings and update these values to match your screen."

---

## Exception: WebXPHP Transpiler Mode

**ONLY create `.php` files if user explicitly says:**
- "Transpile this to PHP"
- "I need PHP code"
- "Use WebXPHP mode"

**Then provide:**
1. The `.prg` source (for reference)
2. Instructions: `webxphp myapp.prg -gx` to generate .php

---

## Where This Rule Is Documented

This critical rule has been added to **3 key files** in the AI training data:

### 1. AI_QUICK_START.md
**Section:** "🚨 CRITICAL: Output Format Rules"
**Location:** Near the top, before "Essential Reading Order"
**Purpose:** First thing AI sees when starting a WebX task

### 2. webx_designer_workflow.md
**Section:** "🚨 CRITICAL OUTPUT FORMAT RULE"
**Location:** Right after "Purpose", before "The Workflow"
**Purpose:** Prevents AI from generating web files when enhancing layouts

### 3. webx_language_rules.md
**Section:** "🚨 CRITICAL: AI Code Generation Output Format"
**Location:** Right after "Introduction", before language rules
**Purpose:** Fundamental rule embedded in the language reference

---

## User Intent Detection Examples

### Example 1: Generic Web Request
**User:** "Create a login page"

**AI Should:**
- Generate `login.prg` with TWindow, TLayout, TGet controls
- Use WebX classes
- NOT create `login.html`

### Example 2: PHP Request
**User:** "I need PHP code for this"

**AI Should:**
- Generate `myapp.prg` first
- Explain: "Run `webxphp myapp.prg -gx` to transpile to PHP"
- NOT directly create `.php` file

### Example 3: HTML Output Request
**User:** "Show me the HTML output"

**AI Should:**
- Explain: "WebX generates HTML at runtime"
- Show the `.prg` source code
- NOT create static `.html` file

### Example 4: FiveWin Request
**User:** "Create a FiveWin dialog"

**AI Should:**
- Generate `.prg` with FiveWin-compatible API
- Use DEFINE DIALOG syntax (if user has FiveWin.ch)
- NOT create `.rc` resource file

---

## Why This Rule Protects Your IP

**What's NOT in the training data:**
- ❌ WebX source code (.prg implementations of classes)
- ❌ Transpiler source (genphp.c)
- ❌ Compiler binaries (webxphp.exe)
- ❌ HTML generation algorithms
- ❌ Rendering logic

**What IS in the training data:**
- ✅ API documentation (TWindow():New parameters)
- ✅ Usage examples (how to call methods)
- ✅ Syntax rules (Harbour language)
- ✅ Best practices

**This rule ensures AI generates USER CODE (.prg), not framework internals.**

---

## Summary

**The Golden Rule:**
> When working with WebX, ALWAYS generate `.prg` files (Harbour source code), NEVER generate `.html`, `.php`, `.css`, or `.js` files unless explicitly requested by the user.

**Why:**
- WebX generates web output AT RUNTIME from `.prg` source
- User writes Harbour code, WebX handles HTML/CSS/JS generation
- Prevents AI from bypassing the WebX framework
- Protects proprietary rendering logic

**Result:**
- Users get correct WebX applications
- AI understands WebX is a compiler, not a template engine
- Your proprietary technology remains protected

---

© 2025 Eric Lendvai & Byron Henderson (MayaPOS) — Licensed under CC BY-NC-SA 4.0
