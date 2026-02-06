# Repository Separation Summary

**Date:** 2026-01-11
**Action:** Separated public docs (mayapos) from internal secrets (webx)
**Reason:** Security + Clean repository structure

---

## 📁 7 Repositories in htdocs

**Confirmed structure:**
```
c:/xampp2025/htdocs/
├── webx/           # Main development (PRIVATE - NOT published)
├── mayapos/        # Public documentation (PUBLISHED to GitHub)
├── clipperWe/      # (separate repo)
├── harbour/        # (separate repo)
├── minimart/       # (separate repo)
├── oldxb/          # (separate repo)
└── oldxHbrPHP/     # (separate repo)
```

**Rule:** Keep repos separate. NO MIXING.

---

## 🔒 What Goes Where

### WEBX Repo (PRIVATE - Development)

**Location:** `htdocs/webx/`

**Contains:**
```
webx/
├── docs/internal/ai-training/     # INTERNAL: Compiler secrets
│   ├── CORE_TRANSPILER_RULES.md   # Transpiler architecture
│   ├── standard_signatures.json    # API internals
│   ├── training_dataset.jsonl      # Compiler patterns
│   ├── AI_AGENT_ONBOARDING.md     # Internal workflows
│   └── ... (internal files)
│
├── webx-ai-training/              # PUBLIC: User docs (source)
│   ├── webx_language_rules_ESSENTIALS.md
│   ├── webx_gui_classes.md
│   └── ... (public files)
│
├── source/classes/                # WebX class sources
├── webxphp_classes/               # Generated PHP
├── WebXPHP/                       # Transpiler
└── samples/                       # Samples
```

**Status:** NOT published (development only)

---

### MAYAPOS Repo (PUBLIC - Documentation)

**Location:** `htdocs/mayapos/`

**Contains:**
```
mayapos/
├── webx-ai-training/              # PUBLIC: User docs ONLY
│   ├── webx_language_rules_ESSENTIALS.md  (copied from webx)
│   ├── webx_language_rules_COMPLETE.md    (copied from webx)
│   ├── webx_gui_classes.md                (copied from webx)
│   ├── webx_deployment_options.md         (copied from webx)
│   └── ... (public docs only)
│
└── README.md                      # Repo description
```

**Status:** PUBLISHED to GitHub (safe)

**What's NOT here:**
- ❌ CORE_TRANSPILER_RULES.md (compiler secrets)
- ❌ standard_signatures.json (API internals)
- ❌ training_dataset.jsonl (compiler patterns)
- ❌ Any internal development files

---

## 📋 Copy Process

### Manual Copy (When Updating Docs)

```bash
# 1. Edit in webx (source)
cd c:/xampp2025/htdocs/webx/webx-ai-training
# ... make changes to public docs ...

# 2. Copy to mayapos (public)
cp -v *.md ../../mayapos/webx-ai-training/
cp -rv webx_functions/ How_to_Interface_Between_C_and_WebX/ ../../mayapos/webx-ai-training/

# 3. Publish mayapos
cd ../../mayapos
git add webx-ai-training/
git commit -m "docs: Update WebX documentation"
git push origin main
```

### What to Copy (PUBLIC ONLY)

**✅ COPY to mayapos:**
- webx_language_rules_ESSENTIALS.md
- webx_language_rules_COMPLETE.md
- webx_gui_classes.md
- webx_deployment_options.md
- webx_designer_workflow.md
- AI_QUICK_START.md
- personal_coding_standards.md
- OUTPUT_FORMAT_RULES.md
- SPEC_webx_functions.md
- CREDITS.md
- README.md
- TRIMMING_SUMMARY.md
- webx_functions/ (directory)
- How_to_Interface_Between_C_and_WebX/ (directory)

**❌ NEVER COPY to mayapos (INTERNAL):**
- CORE_TRANSPILER_RULES.md
- standard_signatures.json
- training_dataset.jsonl
- AI_AGENT_ONBOARDING.md
- AI_TRAINING_SUMMARY.md
- FINE_TUNING_PROVIDERS_GUIDE.md
- PRIVACY_AND_USAGE_GUIDE.md
- ORGANIZATION_SUMMARY.md
- SECURITY_REORGANIZATION.md
- startup_prompt.txt
- README_INTERNAL.md

---

## 🎯 Benefits

### 1. Security

**Before:** Risk of exposing compiler secrets
**After:** Secrets in webx repo (NOT published), public docs in mayapos repo

**Protected:**
- 182 opcode handling logic
- OOP→Functional conversion patterns
- Bug fix strategies
- Internal development workflows

### 2. Clean Repositories

**Before:** Everything mixed in one repo
**After:** Clear separation:
- webx = development (private)
- mayapos = documentation (public)

### 3. Selective Publishing

**Can publish:**
- ✅ User documentation
- ✅ Language guides
- ✅ Deployment guides
- ✅ Class references

**Cannot expose:**
- ❌ Compiler internals
- ❌ Transpiler architecture
- ❌ Training datasets
- ❌ Development workflows

---

## ✅ Verification

**Checked mayapos repo:**
```bash
cd c:/xampp2025/htdocs/mayapos/webx-ai-training

# PUBLIC files present: YES
ls *.md  # 15 files ✅

# INTERNAL secrets absent: CORRECT
ls CORE_TRANSPILER_RULES.md          # No such file ✅
ls standard_signatures.json           # No such file ✅
ls training_dataset.jsonl             # No such file ✅
```

**Result:** ✅ mayapos repo is PUBLIC-SAFE

---

## 📊 File Count

| Location | Public Docs | Internal Secrets | Total |
|----------|-------------|------------------|-------|
| webx/webx-ai-training/ | 12 files | 0 | 12 |
| webx/docs/internal/ai-training/ | 0 | 9 files | 9 |
| mayapos/webx-ai-training/ | 15 files | 0 | 15 |

**Status:** ✅ Correctly separated

---

## 🚨 CRITICAL RULES

### Rule #1: Edit in webx, Copy to mayapos

**Source of truth:** `webx/webx-ai-training/`
**Published version:** `mayapos/webx-ai-training/`

**Never edit directly in mayapos** (changes will be lost when copying from webx).

### Rule #2: Never Copy Internal Files

**Internal stays internal:**
- `webx/docs/internal/ai-training/` → NEVER copy to mayapos

**Public stays public:**
- `webx/webx-ai-training/` → Copy to mayapos for publishing

### Rule #3: Keep Repos Separate

**7 repos in htdocs:**
- Each is independent
- NO mixing between repos
- Each has own git history

---

## 🔄 Workflow Summary

```
1. Develop in webx repo
   ├─ Edit public docs: webx/webx-ai-training/
   ├─ Edit internal docs: webx/docs/internal/ai-training/
   └─ Commit to webx repo (NOT published)

2. Copy public docs to mayapos
   └─ cp webx/webx-ai-training/*.md mayapos/webx-ai-training/

3. Publish mayapos repo
   ├─ git add webx-ai-training/
   ├─ git commit -m "docs: Update"
   └─ git push origin main (PUBLISHED)
```

---

**Status:** ✅ COMPLETE
**Repos Separated:** YES
**Security:** PROTECTED
**Last Updated:** 2026-01-11

**Remember: webx = development (private), mayapos = docs (public)** 🔒
