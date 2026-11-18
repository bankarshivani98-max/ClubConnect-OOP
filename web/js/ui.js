// ClubConnect - shared UI motion helpers (ripple on buttons, animated KPI numbers)
(function () {
    'use strict';
    const reduce = window.matchMedia && window.matchMedia('(prefers-reduced-motion: reduce)').matches;

    window.ClubConnectUI = window.ClubConnectUI || {};
    window.ClubConnectUI.escapeHtml = function (value) {
        return String(value).replace(/[&<>"']/g, character => ({
            '&': '&amp;',
            '<': '&lt;',
            '>': '&gt;',
            '"': '&quot;',
            "'": '&#39;'
        })[character]);
    };

    // 1) Click ripple on every .btn
    if (!reduce) {
        document.addEventListener('click', function (e) {
            const btn = e.target.closest('.btn');
            if (!btn || btn.disabled || btn.classList.contains('disabled')) return;
            const r = btn.getBoundingClientRect();
            const size = Math.max(r.width, r.height);
            const dot = document.createElement('span');
            dot.className = 'ripple-fx';
            dot.style.width = dot.style.height = size + 'px';
            dot.style.left = (e.clientX - r.left - size / 2) + 'px';
            dot.style.top = (e.clientY - r.top - size / 2) + 'px';
            btn.appendChild(dot);
            dot.addEventListener('animationend', function () { dot.remove(); });
        });
    }

    // 2) Count-up for dashboard stat numbers (#statRevenue, #statEnrollments, #statPending)
    //    The page scripts keep setting textContent as before; we just animate what they set.
    function animateNumber(el) {
        const text = el.textContent.trim();
        const m = text.match(/^(\D*?)([\d,]*\.?\d+)(.*)$/);
        if (!m) return;
        const prefix = m[1], suffix = m[3];
        const decimals = (m[2].split('.')[1] || '').length;
        const target = parseFloat(m[2].replace(/,/g, ''));
        if (!isFinite(target) || target === 0) return;
        const fmt = function (v) { return prefix + v.toFixed(decimals) + suffix; };
        const start = performance.now(), dur = 800;
        el.dataset.counting = '1';
        (function tick(now) {
            const t = Math.min(1, (now - start) / dur);
            const eased = 1 - Math.pow(1 - t, 3);
            el.textContent = t < 1 ? fmt(target * eased) : text;
            if (t < 1) requestAnimationFrame(tick);
            else setTimeout(function () { delete el.dataset.counting; }, 0); // after observer has seen our last write
        })(start);
    }
    if (!reduce && 'MutationObserver' in window) {
        ['statRevenue', 'statEnrollments', 'statPending'].forEach(function (id) {
            const el = document.getElementById(id);
            if (!el) return;
            new MutationObserver(function () {
                if (el.dataset.counting) return;   // ignore our own writes
                animateNumber(el);
            }).observe(el, { childList: true, characterData: true, subtree: true });
        });
    }
})();
