# Security Policy

## Supported Versions

| Version | Supported |
|---------|-----------|
| Beta (current) | Yes |
| Future releases | Yes |

## Reporting a Vulnerability

We take security seriously. If you discover a vulnerability in WebX:

### DO NOT

- Open a public GitHub issue
- Discuss the vulnerability in public forums
- Exploit the vulnerability beyond proof of concept

### DO

1. **Email us directly:** mayabuilders@gmail.com
2. **Subject line:** SECURITY - [Brief description]
3. **Include:**
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact assessment
   - Your suggested fix (optional but appreciated)

### Response Timeline

| Stage | Timeline |
|-------|----------|
| Acknowledgment | Within 48 hours |
| Initial assessment | Within 7 days |
| Status update | Within 14 days |
| Fix release | Depends on severity |

### Severity Levels

| Severity | Description | Target Fix Time |
|----------|-------------|-----------------|
| **Critical** | RCE, SQL injection, auth bypass | 24-72 hours |
| **High** | XSS, CSRF, data exposure | 1-2 weeks |
| **Medium** | Information disclosure, DoS | 2-4 weeks |
| **Low** | Best practice violations | Next release |

## Security Features

WebX includes automatic protections against common vulnerabilities:

- **CSRF Protection** - Automatic token generation/validation
- **XSS Prevention** - Output encoding by default
- **Session Security** - HttpOnly cookies
- **Input Sanitization** - AJAX action whitelist

See [SECURITY_FEATURES.md](SECURITY_FEATURES.md) for complete details.

## Acknowledgments

We appreciate responsible disclosure. Security researchers who report valid vulnerabilities will be:

- Credited in our security acknowledgments (with permission)
- Notified before any public disclosure
- Given reasonable time to publish their findings after fix

## Contact

- **Security issues:** mayabuilders@gmail.com (subject: SECURITY)
- **General inquiries:** mayabuilders@gmail.com
- **Website:** https://xbasephp.com

---

*This security policy follows industry best practices for responsible disclosure.*
