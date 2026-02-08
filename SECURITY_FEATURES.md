# WebX Security Features

WebX is designed with **security by default**. Unlike most frameworks where developers must manually implement protections, WebX automatically shields applications from common web vulnerabilities.

**Philosophy:** An xBase developer shouldn't need to become a security expert to deploy safely.

---

## Automatic Protections (Enabled by Default)

These protections are active in every WebX application without any configuration:

### 1. CSRF Protection (Cross-Site Request Forgery)

**What it prevents:** Attackers tricking users into submitting malicious requests.

**How WebX protects:**
- Forms automatically generate unique tokens
- Tokens validated on every POST submission
- No developer configuration required

**Implementation:**
```harbour
// Developer writes:
DEFINE FORM oForm TITLE "Login"
   @ 10, 10 GET cUser LABEL "Username"
   @ 40, 10 GET cPass LABEL "Password" PASSWORD
ENDFORM

// WebX automatically:
// - Generates CSRF token
// - Embeds hidden field in form
// - Validates on submission
```

**Functions:** `GENERATECSRFTOKEN()`, `VALIDATECSRFTOKEN()`

---

### 2. XSS Prevention (Cross-Site Scripting)

**What it prevents:** Attackers injecting malicious JavaScript into your pages.

**How WebX protects:**
- All user content HTML-encoded by default
- Uses `htmlspecialchars($text, ENT_QUOTES, 'UTF-8')`
- Applies to: buttons, labels, inputs, grid columns, dialogs, menus

**Example:**
```
User input: <script>alert('hacked')</script>
Rendered as: &lt;script&gt;alert('hacked')&lt;/script&gt;
```

**Developer must explicitly opt-out** to render raw HTML:
```harbour
// Safe (default): HTML-encoded
@ 10, 10 SAY cUserInput TO oWnd

// Explicit raw HTML (when you know the source is safe):
@ 10, 10 SAY PROMPT "<h2>Welcome</h2>" TO oWnd
```

---

### 3. AJAX Action Whitelist

**What it prevents:** Code injection via AJAX requests.

**How WebX protects:**
- Only alphanumeric action names allowed
- Server-side sanitization: removes all special characters
- Only registered functions can be called

**Implementation:**
```php
// Server sanitizes incoming action names:
$action = preg_replace('/[^a-zA-Z0-9_:]/', '', $action);
```

**What this stops:**
- `action=DeleteAll;DROP TABLE users` → `action=DeleteAllDROPTABLEusers` (no match, rejected)
- `action=../../etc/passwd` → `action=etcpasswd` (no match, rejected)
- `action=eval(malicious)` → `action=evalmalicious` (no match, rejected)

---

### 4. Secure Session Cookies

**What it prevents:** Session hijacking via JavaScript or network interception.

**How WebX protects:**
- **HttpOnly flag** - Cookies cannot be accessed by JavaScript
- **Secure flag** - Cookies only sent over HTTPS (when configured)
- **Proper cleanup** - Session fully destroyed on logout

**Implementation:**
```php
// WebX automatically sets:
setcookie(session_name(), '', time() - 42000,
    $params["path"], $params["domain"],
    $params["secure"], $params["httponly"]  // <-- Security flags
);
```

---

### 5. JavaScript Parameter Escaping

**What it prevents:** Injection attacks in AJAX callbacks.

**How WebX protects:**
- `EscapeJs()` function sanitizes all string parameters
- Prevents breaking out of JavaScript string context
- Applied automatically in WEBX_CALL()

**Example:**
```harbour
// Developer writes:
oButton:bAction := {|| WEBX_CALL("SaveRecord", cUserInput) }

// WebX escapes the parameter:
// If cUserInput = "test'); deleteAll('"
// Becomes: "test\'); deleteAll(\'"
// Safely contained in string context
```

---

## Comparison with Other Frameworks

| Protection | Raw PHP | Laravel | Django | WebX |
|------------|---------|---------|--------|------|
| **CSRF** | Manual | Middleware (opt-in) | Middleware | **Automatic** |
| **XSS** | Manual | Blade (opt-in) | Template (opt-in) | **Automatic** |
| **Session HttpOnly** | Manual (`php.ini`) | Config file | Settings | **Automatic** |
| **Input Sanitization** | Manual | Manual | Manual | **Automatic** |
| **JS Escaping** | Manual | Manual | Manual | **Automatic** |

**Key difference:** In WebX, you have to actively *disable* protections to create a vulnerability. In most frameworks, you have to actively *enable* them to be safe.

---

## What WebX Does NOT Handle (Your Responsibility)

WebX provides application-level security. You're still responsible for:

### Infrastructure Security
- Firewall configuration
- SSL/TLS certificates (HTTPS)
- Server hardening
- Regular OS updates

### Database Security
- Database credentials management
- Database access controls
- Backup encryption

### Business Logic Security
- Authorization (who can access what)
- Rate limiting (coming in future release)
- Password policies

---

## Security Roadmap

**Planned for future releases:**

| Feature | Status | Description |
|---------|--------|-------------|
| Rate Limiting | Planned | Per-session/IP request limits |
| SQL Prepared Statements | Planned | Helper for database layer |
| Content Security Policy | Planned | CSP header generation |
| Security Headers | Planned | X-Frame-Options, X-Content-Type-Options |

---

## Reporting Security Issues

If you discover a security vulnerability:

1. **DO NOT** open a public GitHub issue
2. Email: mayabuilders@gmail.com with subject: "SECURITY"
3. Include: Description, reproduction steps, potential impact

See [SECURITY.md](SECURITY.md) for our full security policy.

---

## Implementation Details

For developers interested in the code:

| Feature | File | Line |
|---------|------|------|
| CSRF Generation | `webx_form.php` | `GENERATECSRFTOKEN()` |
| CSRF Validation | `webx_form.php` | `VALIDATECSRFTOKEN()` |
| XSS Encoding | `webx_runtime.php` | Line ~5708 |
| AJAX Whitelist | `webx_runtime.php` | Line ~458 |
| Session Security | `webx_runtime.php` | Line ~506 |
| JS Escaping | `webx_ajax.prg` | `EscapeJs()` |

---

**WebX Security:** Protecting xBase developers who shouldn't need to become security experts.
