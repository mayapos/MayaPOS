# WebX AI Training Resources - Public Documentation

**Repository:** MayaPOS Public Documentation
**Author:** Bayron Landaverry
**Company:** xBasePHP.com
**Last Updated:** 2026-02-05

---

## ⚠️ IMPORTANT: This is PUBLIC Documentation ONLY

**This repository contains:**
- ✅ User-facing WebX documentation
- ✅ Safe to publish on GitHub
- ✅ NO compiler internals or secrets

**What's NOT here (kept internal):**
- ❌ CORE_TRANSPILER_RULES.md (compiler internals - in webx repo)
- ❌ standard_signatures.json (API internals - in webx repo)
- ❌ training_dataset.jsonl (compiler patterns - in webx repo)
- ❌ AI_AGENT_ONBOARDING.md (internal workflows - in webx repo)

**Location of internal files:** `htdocs/webx/docs/internal/ai-training/` (NOT published)

---

## 📦 Repository Structure

```
htdocs/
├── webx/                              # Main development repo (NOT published)
│   ├── docs/internal/ai-training/     # INTERNAL: Compiler secrets
│   │   ├── CORE_TRANSPILER_RULES.md   # (secret)
│   │   ├── standard_signatures.json    # (secret)
│   │   └── training_dataset.jsonl      # (secret)
│   └── webx-ai-training/              # PUBLIC: User docs (copied to mayapos)
│
└── mayapos/                           # Public repo (published to GitHub)
    └── webx-ai-training/              # PUBLIC: User docs ONLY
        ├── webx_language_rules_ESSENTIALS.md
        ├── webx_gui_classes.md
        └── ... (public docs)
```

**Rule:** Copy from `webx/webx-ai-training/` to `mayapos/webx-ai-training/` for publishing.

---

## 📚 What's In This Repository

### Language & Syntax Guides

1. **[webx_language_rules_ESSENTIALS.md](webx_language_rules_ESSENTIALS.md)** (13 KB) - AI-Optimized ⭐
   - WebX-specific patterns only
   - 93.8% smaller than COMPLETE
   - Recommended for AI agents

2. **[webx_language_rules_COMPLETE.md](webx_language_rules_COMPLETE.md)** (208 KB) - Full Reference
   - Comprehensive Harbour + WebX syntax
   - For human developers

3. **[webx_gui_classes.md](webx_gui_classes.md)** (19 KB) - Class Reference
   - TWindow, TButton, TGet, TSay, TMenu
   - TAccordion, TCarousel, TLayout (WebX-specific)

4. **[AI_QUICK_START.md](AI_QUICK_START.md)** (22 KB) - Quick Start
   - Getting started with WebX + AI
   - Common patterns

### Deployment & Workflow

5. **[webx_deployment_options.md](webx_deployment_options.md)** (20 KB)
   - 6 deployment modes
   - Production setup guides

6. **[webx_designer_workflow.md](webx_designer_workflow.md)** (20 KB)
   - Visual designer usage
   - TLayout Designer tool

### Runtime Libraries (NEW!)

7. **[WEBX_RUNTIME_LIBRARIES.md](WEBX_RUNTIME_LIBRARIES.md)** (40 KB) - Complete Function Reference
   - 2,000+ PHP function stubs for Harbour compatibility
   - Harbour RTL (792 functions)
   - Clipper Tools (200+ functions)
   - NanForum Library (100+ functions)
   - PCRE Regex (40+ functions)
   - TIP Protocol - HTTP/SMTP/FTP (50+ functions)
   - FiveWin compatibility (300+ functions)

### Standards & Specs

8. **[personal_coding_standards.md](personal_coding_standards.md)** (10 KB)
   - WebX coding conventions
   - Style guide

9. **[OUTPUT_FORMAT_RULES.md](OUTPUT_FORMAT_RULES.md)** (8 KB)
   - HTML/CSS/JS output formatting

10. **[SPEC_webx_functions.md](SPEC_webx_functions.md)** (5 KB)
    - Function specifications

---

## 🚀 Quick Start for AI Agents

**Load ESSENTIALS first (recommended):**

```bash
# AI-optimized (13 KB - WebX-specific only)
webx_language_rules_ESSENTIALS.md
webx_gui_classes.md
AI_QUICK_START.md
```

**Total:** ~54 KB context
**Token cost:** ~13,500 tokens ($0.005 per load with Gemini)

---

## 🔒 Security Note

**This repository is PUBLIC-SAFE:**
- ✅ Contains user documentation only
- ✅ No compiler internals
- ✅ No API secrets
- ✅ No training datasets
- ✅ Safe to publish on GitHub

**Competitive advantage protected:**
- Compiler internals in `webx/docs/internal/` (NOT published)
- 182 opcode handling (NOT published)
- OOP→Functional conversion logic (NOT published)
- Bug fix patterns (NOT published)

---

## 📊 File Statistics

| File | Size | Purpose |
|------|------|---------|
| webx_language_rules_ESSENTIALS.md | 13 KB | AI-optimized |
| webx_language_rules_COMPLETE.md | 208 KB | Full reference |
| webx_gui_classes.md | 33 KB | Class docs (110+ classes) |
| WEBX_RUNTIME_LIBRARIES.md | 40 KB | **2,000+ function stubs** |
| webx_deployment_options.md | 20 KB | Deployment |
| AI_QUICK_START.md | 22 KB | Quick start |

**Total:** ~336 KB public documentation
**Runtime Functions:** 2,000+ (Harbour RTL, Clipper Tools, NanForum, Regex, TIP, FiveWin)

---

## 🔄 Update Process

**To update public docs:**

1. Edit in `webx/webx-ai-training/` (source)
2. Copy to `mayapos/webx-ai-training/` (public)
3. Commit and push mayapos repo

**Command:**
```bash
cd c:/xampp2025/htdocs/webx/webx-ai-training
cp -v *.md ../../mayapos/webx-ai-training/
cd ../../mayapos
git add webx-ai-training/
git commit -m "docs: Update WebX documentation"
git push origin main
```

**NEVER copy from `webx/docs/internal/ai-training/` (contains secrets!)**

---

## 🙏 Credits

**Author:** Bayron Landaverry  
**Company:** xBasePHP.com  
**Contributors:** Eric Lendvai (original training dataset)
**Harbour Foundation:** Harbour Project

See [CREDITS.md](CREDITS.md) for full attribution.

---

## 📞 Support

**WebX Framework:**
- Website: https://xBasePHP.com
- Email: info@xBasePHP.com

**GitHub Issues:**
- Report issues in this repository
- For compiler bugs: Contact xBasePHP.com directly (NOT public)

---

**Status:** ✅ PUBLIC DOCUMENTATION ONLY
**Safe to Publish:** YES
**Last Updated:** 2026-02-05
**Author:** Bayron Landaverry (xBasePHP.com)

**Remember: This repo contains PUBLIC user docs. Compiler internals stay in webx repo!** 🔒
