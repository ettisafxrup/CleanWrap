/* ============================================================
   CleanWrap — animations.js
   Particles, mouse parallax, scroll reveal, counters, progress
   ============================================================ */
;(function () {
  "use strict"

  const reduced = window.matchMedia("(prefers-reduced-motion: reduce)").matches

  /* ---------------- Particle field ---------------- */
  function initParticles() {
    const canvas = document.getElementById("particles")
    if (!canvas || reduced) return
    const ctx = canvas.getContext("2d")
    let w,
      h,
      dots = []

    function resize() {
      w = canvas.width = window.innerWidth
      h = canvas.height = window.innerHeight
      const count = Math.min(90, Math.floor((w * h) / 22000))
      dots = Array.from({ length: count }, () => ({
        x: Math.random() * w,
        y: Math.random() * h,
        r: Math.random() * 1.8 + 0.5,
        vx: (Math.random() - 0.5) * 0.25,
        vy: (Math.random() - 0.5) * 0.25,
        a: Math.random() * 0.5 + 0.2,
      }))
    }

    function frame() {
      ctx.clearRect(0, 0, w, h)
      for (let i = 0; i < dots.length; i++) {
        const d = dots[i]
        d.x += d.vx
        d.y += d.vy
        if (d.x < 0) d.x = w
        if (d.x > w) d.x = 0
        if (d.y < 0) d.y = h
        if (d.y > h) d.y = 0
        ctx.beginPath()
        ctx.arc(d.x, d.y, d.r, 0, Math.PI * 2)
        ctx.fillStyle = "rgba(147,197,253," + d.a + ")"
        ctx.fill()

        for (let j = i + 1; j < dots.length; j++) {
          const o = dots[j]
          const dx = d.x - o.x,
            dy = d.y - o.y
          const dist = dx * dx + dy * dy
          if (dist < 14000) {
            ctx.beginPath()
            ctx.moveTo(d.x, d.y)
            ctx.lineTo(o.x, o.y)
            ctx.strokeStyle =
              "rgba(96,165,250," + 0.1 * (1 - dist / 14000) + ")"
            ctx.lineWidth = 1
            ctx.stroke()
          }
        }
      }
      requestAnimationFrame(frame)
    }

    resize()
    window.addEventListener("resize", resize)
    frame()
  }

  /* ---------------- Scroll reveal ---------------- */
  function initReveal() {
    const items = document.querySelectorAll(".reveal")
    if (!("IntersectionObserver" in window)) {
      items.forEach((el) => el.classList.add("visible"))
      return
    }
    const io = new IntersectionObserver(
      (entries) => {
        entries.forEach((entry, i) => {
          if (entry.isIntersecting) {
            const el = entry.target
            setTimeout(() => el.classList.add("visible"), Math.min(i * 70, 350))
            io.unobserve(el)
          }
        })
      },
      { threshold: 0.12, rootMargin: "0px 0px -60px 0px" },
    )
    items.forEach((el) => io.observe(el))
  }

  /* ---------------- Animated counters ---------------- */
  function initCounters() {
    const nodes = document.querySelectorAll(
      "[data-counter]:not([data-live-counter])",
    )
    if (!nodes.length) return

    function run(el) {
      const target = parseFloat(el.getAttribute("data-counter")) || 0
      const suffix = el.getAttribute("data-suffix") || ""
      const dur = 1600
      const start = performance.now()
      function tick(now) {
        const p = Math.min((now - start) / dur, 1)
        const eased = 1 - Math.pow(1 - p, 3)
        const val = Math.round(target * eased)
        el.textContent = val.toLocaleString() + suffix
        if (p < 1) requestAnimationFrame(tick)
      }
      requestAnimationFrame(tick)
    }

    const io = new IntersectionObserver(
      (entries) => {
        entries.forEach((e) => {
          if (e.isIntersecting) {
            run(e.target)
            io.unobserve(e.target)
          }
        })
      },
      { threshold: 0.4 },
    )
    nodes.forEach((n) => io.observe(n))
  }

  /* ---------------- Mouse parallax ---------------- */
  function initParallax() {
    if (reduced) return
    const layers = document.querySelectorAll(".parallax")
    if (!layers.length) return
    let tx = 0,
      ty = 0,
      cx = 0,
      cy = 0

    window.addEventListener("mousemove", (e) => {
      tx = (e.clientX / window.innerWidth - 0.5) * 2
      ty = (e.clientY / window.innerHeight - 0.5) * 2
    })

    ;(function loop() {
      cx += (tx - cx) * 0.06
      cy += (ty - cy) * 0.06
      layers.forEach((l) => {
        const d = parseFloat(l.getAttribute("data-depth")) || 10
        l.style.transform =
          "translate3d(" +
          (cx * d).toFixed(2) +
          "px," +
          (cy * d).toFixed(2) +
          "px,0)"
      })
      requestAnimationFrame(loop)
    })()
  }

  /* ---------------- Card spotlight hover ---------------- */
  function initSpotlight() {
    document.addEventListener("mousemove", (e) => {
      const card = e.target.closest(".card")
      if (!card) return
      const r = card.getBoundingClientRect()
      card.style.setProperty("--mx", e.clientX - r.left + "px")
      card.style.setProperty("--my", e.clientY - r.top + "px")
    })
  }

  /* ---------------- Scroll progress bar ---------------- */
  function initProgress() {
    const bar = document.getElementById("progress")
    if (!bar) return
    function update() {
      const scrolled = window.scrollY
      const max = document.documentElement.scrollHeight - window.innerHeight
      bar.style.width = (max > 0 ? (scrolled / max) * 100 : 0) + "%"
    }
    window.addEventListener("scroll", update, { passive: true })
    window.addEventListener("resize", update)
    update()
  }

  window.CleanWrapAnimations = {
    init() {
      initParticles()
      initReveal()
      initCounters()
      initParallax()
      initSpotlight()
      initProgress()
    },
    refreshReveal: initReveal,
    refreshCounters: initCounters,
  }
})()
