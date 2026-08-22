/* ============================================================
   CleanWrap — main.js
   Content rendering, navigation, accordion, theme, utilities
   ============================================================ */
;(function () {
  "use strict"

  /* ---------------- Icon library ---------------- */
  const I = {
    folder:
      '<path d="M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z"/>',
    copy: '<rect x="9" y="9" width="13" height="13" rx="2"/><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"/>',
    hash: '<line x1="4" y1="9" x2="20" y2="9"/><line x1="4" y1="15" x2="20" y2="15"/><line x1="10" y1="3" x2="8" y2="21"/><line x1="16" y1="3" x2="14" y2="21"/>',
    search:
      '<circle cx="11" cy="11" r="8"/><line x1="21" y1="21" x2="16.65" y2="16.65"/>',
    report:
      '<path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"/><polyline points="14 2 14 8 20 8"/><line x1="9" y1="15" x2="15" y2="15"/><line x1="9" y1="11" x2="13" y2="11"/>',
    mouse:
      '<rect x="6" y="2" width="12" height="20" rx="6"/><line x1="12" y1="7" x2="12" y2="10"/>',
    power:
      '<path d="M18.36 6.64a9 9 0 1 1-12.73 0"/><line x1="12" y1="2" x2="12" y2="12"/>',
    plus: '<path d="M22 19a2 2 0 0 1-2 2H4a2 2 0 0 1-2-2V5a2 2 0 0 1 2-2h5l2 3h9a2 2 0 0 1 2 2z"/><line x1="12" y1="11" x2="12" y2="17"/><line x1="9" y1="14" x2="15" y2="14"/>',
    tag: '<path d="M20.59 13.41 12 22l-9-9V3h10z"/><circle cx="7.5" cy="7.5" r="1.2"/>',
    shield:
      '<path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10z"/><polyline points="9 12 11 14 15 10"/>',
    bolt: '<polygon points="13 2 3 14 12 14 11 22 21 10 12 10 13 2"/>',
    feather:
      '<path d="M20.24 12.24a6 6 0 0 0-8.49-8.49L5 10.5V19h8.5z"/><line x1="16" y1="8" x2="2" y2="22"/>',
    code: '<polyline points="16 18 22 12 16 6"/><polyline points="8 6 2 12 8 18"/>',
    windows:
      '<rect x="3" y="3" width="8" height="8"/><rect x="13" y="3" width="8" height="8"/><rect x="3" y="13" width="8" height="8"/><rect x="13" y="13" width="8" height="8"/>',
    image:
      '<rect x="3" y="3" width="18" height="18" rx="2"/><circle cx="8.5" cy="8.5" r="1.5"/><polyline points="21 15 16 10 5 21"/>',
    video:
      '<polygon points="23 7 16 12 23 17 23 7"/><rect x="1" y="5" width="15" height="14" rx="2"/>',
    music:
      '<path d="M9 18V5l12-2v13"/><circle cx="6" cy="18" r="3"/><circle cx="18" cy="16" r="3"/>',
    pdf: '<path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"/><polyline points="14 2 14 8 20 8"/>',
    doc: '<path d="M14 2H6a2 2 0 0 0-2 2v16a2 2 0 0 0 2 2h12a2 2 0 0 0 2-2V8z"/><line x1="8" y1="13" x2="16" y2="13"/><line x1="8" y1="17" x2="14" y2="17"/>',
    exe: '<rect x="4" y="4" width="16" height="16" rx="2"/><path d="M9 9h6v6H9z"/>',
    archive:
      '<path d="M21 8v13H3V8"/><rect x="1" y="3" width="22" height="5" rx="1"/><line x1="10" y1="12" x2="14" y2="12"/>',
    other:
      '<circle cx="12" cy="12" r="9"/><line x1="12" y1="8" x2="12" y2="12"/><line x1="12" y1="16" x2="12.01" y2="16"/>',
    grid: '<rect x="3" y="3" width="7" height="7"/><rect x="14" y="3" width="7" height="7"/><rect x="14" y="14" width="7" height="7"/><rect x="3" y="14" width="7" height="7"/>',
    layers:
      '<polygon points="12 2 2 7 12 12 22 7 12 2"/><polyline points="2 17 12 22 22 17"/><polyline points="2 12 12 17 22 12"/>',
    move: '<polyline points="5 9 2 12 5 15"/><polyline points="9 5 12 2 15 5"/><polyline points="15 19 12 22 9 19"/><polyline points="19 9 22 12 19 15"/><line x1="2" y1="12" x2="22" y2="12"/><line x1="12" y1="2" x2="12" y2="22"/>',
  }

  const svg = (p) =>
    '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round">' +
    p +
    "</svg>"

  /* ---------------- Data ---------------- */
  const FEATURES = [
    {
      i: I.folder,
      t: "Automatic file organization",
      d: "Point CleanWrap at any folder and every file is sorted into a clean category structure in a single pass — no rules to write.",
    },
    {
      i: I.copy,
      t: "Smart duplicate detection",
      d: "Combines filename heuristics with size checks to shortlist duplicates before a single byte is read from disk.",
    },
    {
      i: I.hash,
      t: "Hash-based verification",
      d: "64-bit FNV-1a content hashing confirms that two files are truly identical, eliminating false positives.",
    },
    {
      i: I.search,
      t: "Filename pattern recognition",
      d: "Recognises Windows and browser duplicate patterns like “(1)”, “ - Copy” and “ - Copy (3)” instantly.",
    },
    {
      i: I.report,
      t: "Cleanup reports",
      d: "Every run produces a timestamped _CleanWrap.log listing each move, each duplicate and the space reclaimed.",
    },
    {
      i: I.mouse,
      t: "Explorer context menu",
      d: "Right-click any folder in Windows Explorer and choose “Organize with CleanWrap” — no window required.",
    },
    {
      i: I.power,
      t: "Run on startup",
      d: "Optionally launch with Windows and keep your Downloads folder tidy automatically, in the background.",
    },
    {
      i: I.plus,
      t: "Smart folder creation",
      d: "Category folders are created only when they're needed, so you never end up with empty clutter.",
    },
    {
      i: I.tag,
      t: "Category detection",
      d: "20 built-in categories cover 283 supported extensions, with signature checks for mislabeled files.",
    },
    {
      i: I.shield,
      t: "Safe file moving",
      d: "Atomic moves, automatic collision renaming, locked-file skipping and zero deletions by default.",
    },
    {
      i: I.bolt,
      t: "Fast execution",
      d: "Over a thousand files processed per second on typical hardware — most runs finish before you blink.",
    },
    {
      i: I.feather,
      t: "Lightweight",
      d: "A ~4.3 MB installer, no runtime dependencies, no background service eating your RAM.",
    },
    {
      i: I.code,
      t: "Modern C++20",
      d: "Written with std::filesystem, ranges and concepts for correctness and speed, compiled with full optimisation.",
    },
    {
      i: I.windows,
      t: "Windows native",
      d: "Pure Win32 and the Windows shell API. No Electron, no .NET runtime, no browser engine.",
    },
  ]

  const FILETYPES = [
    {
      i: I.image,
      t: "Images",
      e: ".jpg .png .gif .webp .svg .heic",
    },
    { i: I.pdf, t: "PDFs", e: ".pdf" },
    {
      i: I.video,
      t: "Videos",
      e: ".mp4 .mkv .avi .mov .webm .wmv",
    },
    {
      i: I.music,
      t: "Audio",
      e: ".mp3 .wav .flac .aac .m4a .ogg",
    },
    {
      i: I.code,
      t: "Code",
      e: ".c .cpp .h .py .java .js .ts",
    },
    {
      i: I.exe,
      t: "Executables and Installers",
      e: ".exe .msi .msix .appx .dll .sys",
    },
    {
      i: I.doc,
      t: "Documents",
      e: ".doc .docx .odt .rtf .txt .md",
    },
    {
      i: I.doc,
      t: "Presentations",
      e: ".ppt .pptx .pps .ppsx .odp .key",
    },
    {
      i: I.doc,
      t: "Spreadsheets",
      e: ".xls .xlsx .xlsm .csv .tsv .ods",
    },
    {
      i: I.doc,
      t: "Ebooks",
      e: ".epub .mobi .azw .azw3 .fb2 .djvu",
    },
    {
      i: I.archive,
      t: "Archives and Zips",
      e: ".zip .rar .7z .tar .gz .iso",
    },
    { i: I.doc, t: "Fonts", e: ".ttf .otf .woff .woff2 .eot" },
    {
      i: I.image,
      t: "Design",
      e: ".ai .eps .indd .fig .blend .obj",
    },
    {
      i: I.grid,
      t: "CAD",
      e: ".dwg .dxf .sldprt .sldasm .ipt .iam",
    },
    {
      i: I.grid,
      t: "Data",
      e: ".db .sqlite .sqlite3 .mdb .accdb .parquet",
    },
    { i: I.video, t: "Subtitles", e: ".srt .ass .ssa .sub .vtt .sbv" },
    {
      i: I.layers,
      t: "Virtual Machines",
      e: ".vdi .vmdk .vhd .vhdx .ova .ovf",
    },
    { i: I.shield, t: "Certificates", e: ".cer .crt .pem .der .p12 .pfx" },
    { i: I.other, t: "Torrents", e: ".torrent" },
    { i: I.other, t: "Others", e: "unknown or extensionless files, kept safe" },
  ]

  const SHOTS = [
    {
      t: "Main window",
      d: "The CleanWrap dashboard with target folder, category preview and the single Organize action.",
    },
    {
      t: "Downloads before",
      d: "A real Downloads folder with 1,248 unsorted files spanning every possible file type.",
    },
    {
      t: "Downloads after",
      d: "The same folder after a single run — clean category folders and a report file.",
    },
    {
      t: "Duplicate folder",
      d: "Quarantined duplicates with their matched originals and content hashes shown side by side.",
    },
    {
      t: "Log report",
      d: "The generated _CleanWrap.log opened in Notepad, showing every move and skip decision.",
    },
    {
      t: "Right-click context menu",
      d: "Windows Explorer shell integration adding “Organize with CleanWrap” to any folder.",
    },
    {
      t: "Installer",
      d: "The setup wizard with startup and Explorer integration options on a single screen.",
    },
    {
      t: "Statistics",
      d: "Per-run statistics: files categorised, duplicates found, space reclaimed and elapsed time.",
    },
  ]

  const ROADMAP = [
    {
      t: "Graphical User Interface",
      s: "In progress",
      c: "",
      d: "A full native GUI with live folder preview, per-category toggles and drag-to-reorder rules.",
    },
    {
      t: "Drag & drop",
      s: "In progress",
      c: "",
      d: "Drop any folder onto the CleanWrap window — or its taskbar icon — to organize it instantly.",
    },
    {
      t: "Auto update",
      s: "Next",
      c: "soon",
      d: "Signed delta updates checked in the background so you always run the latest release.",
    },
    {
      t: "Linux support",
      s: "Next",
      c: "soon",
      d: "A portable core with an ELF build for major distributions, sharing the same rules engine.",
    },
    {
      t: "macOS support",
      s: "Planned",
      c: "later",
      d: "Universal binary for Apple Silicon and Intel, with Finder integration.",
    },
    {
      t: "Cloud sync",
      s: "Planned",
      c: "later",
      d: "Sync your category rules and preferences across every machine you use.",
    },
    {
      t: "Undo",
      s: "Planned",
      c: "later",
      d: "One-click rollback of an entire run, reconstructed from the transactional log.",
    },
    {
      t: "Statistics dashboard",
      s: "Planned",
      c: "later",
      d: "Long-term insight into what you download, how much you duplicate and space saved over time.",
    },
  ]

  const FAQ = [
    {
      q: "What does CleanWrap do?",
      a: "CleanWrap scans a folder — usually your Windows Downloads folder — identifies the type of every file inside it, and moves each file into a matching category folder such as Images, Documents or Archives. While doing so it detects duplicate files, quarantines them separately, and writes a full report of everything it did.",
    },
    {
      q: "Does it delete files?",
      a: "No. CleanWrap never deletes anything on its own. Files are moved, not removed, and detected duplicates are placed in a dedicated Duplicates folder so you can review them yourself before deciding. Every single operation is recorded in _CleanWrap.log.",
    },
    {
      q: "How are duplicates detected?",
      a: "In two stages. First, filename patterns such as “file (1).pdf” or “image - Copy.png” and matching file sizes shortlist likely duplicates. Second, each candidate is verified with a 64-bit FNV-1a content hash. A file is only treated as a duplicate when its content hash matches an existing file exactly.",
    },
    {
      q: "Can I undo changes?",
      a: "Manually, yes — because nothing is deleted, restoring a file is a matter of dragging it back. Yet sooner this feature would be available where you can undo an entire run with a single click, reconstructed from the transactional log.",
    },
    {
      q: "Does it support Windows 11?",
      a: "Yes. CleanWrap fully supports Windows 11 and Windows 10 on both x64 and ARM64, including the Windows 11 modern context menu. It requires no .NET runtime or other dependency.",
    },
    {
      q: "Is it free?",
      a: "Completely. CleanWrap is free and open source under the MIT License. There is no paid tier, no trial period, no ads and no telemetry — you can read, modify and redistribute the source on GitHub.",
    },
  ]

  /* ---------------- Rendering ---------------- */
  const setHtml = (id, html) => {
    const node = document.getElementById(id)
    if (node) node.innerHTML = html
  }

  const render = () => {
    setHtml(
      "featureCards",
      FEATURES.map(
        (f) =>
          `<article class="card reveal"><div class="card-icon">${svg(f.i)}</div><h4>${f.t}</h4><p>${f.d}</p></article>`,
      ).join(""),
    )

    setHtml(
      "fileTypeGrid",
      FILETYPES.map(
        (f) =>
          `<div class="ft reveal zoom"><div class="ficon">${svg(f.i)}</div><b>${f.t}</b><small>${f.e}</small></div>`,
      ).join(""),
    )

    setHtml(
      "shotGrid",
      SHOTS.map(
        (s, idx) =>
          `<figure class="shot reveal"><div class="ph">${svg(I.image)}<span>assets/screenshots/screenshot${
            idx + 1
          }.png</span></div><figcaption class="shot-body"><h4>${s.t}</h4><p>${s.d}</p></figcaption></figure>`,
      ).join(""),
    )

    setHtml(
      "roadmapList",
      ROADMAP.map(
        (r) =>
          `<div class="rm reveal from-left"><h4>${r.t} <span class="tag ${r.c}">${r.s}</span></h4><p>${r.d}</p></div>`,
      ).join(""),
    )

    setHtml(
      "faqList",
      FAQ.map(
        (f) =>
          `<div class="acc reveal"><button class="acc-q" type="button" aria-expanded="false"><span>${f.q}</span><span class="chev"><svg width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"/></svg></span></button><div class="acc-a"><p>${f.a}</p></div></div>`,
      ).join(""),
    )
  }

  /* ---------------- GitHub stats ---------------- */
  const GH_REPO = "ettisafxrup/CleanWrap"
  const GH_STATS_CACHE_KEY = "cleanwrap.github-stats"
  const GH_BADGE_URLS = {
    stars: "https://img.shields.io/github/stars/" + GH_REPO + ".json",
    downloads:
      "https://img.shields.io/github/downloads/" + GH_REPO + "/total.json",
  }

  function formatNumber(value, suffix = "") {
    return value.toLocaleString() + suffix
  }

  function updateGithubStats(stars, downloads) {
    const starsNode = document.getElementById("git-stars")
    const downloadsNode = document.getElementById("git-downloads")
    if (starsNode && Number.isFinite(stars)) {
      starsNode.textContent = formatNumber(stars)
      starsNode.setAttribute("data-counter", String(stars))
    }
    if (downloadsNode && Number.isFinite(downloads)) {
      downloadsNode.textContent = formatNumber(downloads, "+")
      downloadsNode.setAttribute("data-counter", String(downloads))
    }
  }

  function parseBadgeValue(value) {
    const match = String(value)
      .trim()
      .toLowerCase()
      .match(/^([\d,.]+)\s*([km]?)$/)
    if (!match) return NaN
    const number = Number(match[1].replace(/,/g, ""))
    const multiplier = match[2] === "m" ? 1000000 : match[2] === "k" ? 1000 : 1
    return Number.isFinite(number) ? Math.round(number * multiplier) : NaN
  }

  async function fetchJson(url) {
    const response = await fetch(url, {
      headers: { Accept: "application/json" },
      cache: "no-store",
    })
    if (!response.ok) throw new Error("request status " + response.status)
    return response.json()
  }

  async function fetchBadgeValue(url) {
    const badge = await fetchJson(url)
    const value = parseBadgeValue(badge && (badge.message || badge.value))
    if (!Number.isFinite(value)) throw new Error("invalid badge value")
    return value
  }

  async function loadGithubStats() {
    let cached = {}
    try {
      cached = JSON.parse(localStorage.getItem(GH_STATS_CACHE_KEY) || "{}")
    } catch (error) {
      console.warn("GitHub stats cache unavailable:", error)
    }

    updateGithubStats(cached.stars, cached.downloads)

    const fetchStars = fetchJson("https://api.github.com/repos/" + GH_REPO)
      .then((data) => {
        const stars = Number(data.stargazers_count)
        if (!Number.isFinite(stars)) throw new Error("invalid star count")
        return stars
      })
      .catch(() => fetchBadgeValue(GH_BADGE_URLS.stars))
      .catch(() => NaN)
    const fetchDownloads = fetchJson(
      "https://api.github.com/repos/" + GH_REPO + "/releases?per_page=100",
    )
      .then((releases) =>
        Array.isArray(releases)
          ? releases.reduce(
              (sum, release) =>
                sum +
                (Array.isArray(release && release.assets)
                  ? release.assets.reduce(
                      (assetSum, asset) =>
                        assetSum + Number(asset.download_count || 0),
                      0,
                    )
                  : 0),
              0,
            )
          : NaN,
      )
      .catch(() => fetchBadgeValue(GH_BADGE_URLS.downloads))
      .catch(() => NaN)

    const [stars, downloads] = await Promise.all([fetchStars, fetchDownloads])
    const stats = {
      stars: Number.isFinite(stars) ? stars : cached.stars,
      downloads: Number.isFinite(downloads) ? downloads : cached.downloads,
    }
    updateGithubStats(stats.stars, stats.downloads)
    try {
      localStorage.setItem(GH_STATS_CACHE_KEY, JSON.stringify(stats))
    } catch (error) {
      console.warn("GitHub stats cache unavailable:", error)
    }
  }

  /* ---------------- Accordion ---------------- */
  function initAccordion() {
    document.addEventListener("click", (e) => {
      const q = e.target.closest(".acc-q")
      if (!q) return
      const acc = q.parentElement
      const panel = acc.querySelector(".acc-a")
      const isOpen = acc.classList.contains("open")

      document.querySelectorAll(".acc.open").forEach((o) => {
        o.classList.remove("open")
        o.querySelector(".acc-a").style.maxHeight = null
        o.querySelector(".acc-q").setAttribute("aria-expanded", "false")
      })

      if (!isOpen) {
        acc.classList.add("open")
        panel.style.maxHeight = panel.scrollHeight + "px"
        q.setAttribute("aria-expanded", "true")
      }
    })
  }

  /* ---------------- Navbar ---------------- */
  function initNav() {
    const nav = document.getElementById("nav")
    const toggle = document.getElementById("navToggle")
    const menu = document.getElementById("mobileMenu")

    const onScroll = () => {
      if (window.scrollY > 24) nav.classList.add("scrolled")
      else nav.classList.remove("scrolled")
    }
    window.addEventListener("scroll", onScroll, { passive: true })
    onScroll()

    if (toggle && menu) {
      toggle.addEventListener("click", () => {
        const open = menu.classList.toggle("open")
        toggle.setAttribute("aria-expanded", String(open))
      })
      menu.addEventListener("click", (e) => {
        if (e.target.tagName === "A") {
          menu.classList.remove("open")
          toggle.setAttribute("aria-expanded", "false")
        }
      })
    }

    // Active link highlighting
    const sections = Array.from(document.querySelectorAll("main section[id]"))
    const links = Array.from(
      document.querySelectorAll(".nav-links a[href^='#']"),
    )
    if (sections.length && links.length && "IntersectionObserver" in window) {
      const io = new IntersectionObserver(
        (entries) => {
          entries.forEach((en) => {
            if (!en.isIntersecting) return
            const id = "#" + en.target.id
            links.forEach((l) =>
              l.classList.toggle("active", l.getAttribute("href") === id),
            )
          })
        },
        { rootMargin: "-45% 0px -50% 0px" },
      )
      sections.forEach((s) => io.observe(s))
    }
  }

  /* ---------------- Theme toggle ---------------- */
  function initTheme() {
    const btn = document.getElementById("themeToggle")
    const icon = document.getElementById("themeIcon")
    const root = document.documentElement
    const sun =
      '<circle cx="12" cy="12" r="4"/><line x1="12" y1="2" x2="12" y2="5"/><line x1="12" y1="19" x2="12" y2="22"/><line x1="2" y1="12" x2="5" y2="12"/><line x1="19" y1="12" x2="22" y2="12"/><line x1="4.9" y1="4.9" x2="7" y2="7"/><line x1="17" y1="17" x2="19.1" y2="19.1"/><line x1="4.9" y1="19.1" x2="7" y2="17"/><line x1="17" y1="7" x2="19.1" y2="4.9"/>'
    const moon = '<path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/>'

    let saved = null
    try {
      saved = localStorage.getItem("cleanwrap-theme")
    } catch (_) {}
    const theme = saved || "dark"
    root.setAttribute("data-theme", theme)
    if (icon) icon.innerHTML = theme === "dark" ? moon : sun

    if (btn) {
      btn.addEventListener("click", () => {
        const next =
          root.getAttribute("data-theme") === "dark" ? "light" : "dark"
        root.setAttribute("data-theme", next)
        if (icon) icon.innerHTML = next === "dark" ? moon : sun
        try {
          localStorage.setItem("cleanwrap-theme", next)
        } catch (_) {}
      })
    }
  }

  /* ---------------- Ripple buttons ---------------- */
  function initRipple() {
    document.addEventListener("click", (e) => {
      const btn = e.target.closest(".btn")
      if (!btn) return
      const r = btn.getBoundingClientRect()
      const size = Math.max(r.width, r.height)
      const span = document.createElement("span")
      span.className = "ripple"
      span.style.width = span.style.height = size + "px"
      span.style.left = e.clientX - r.left - size / 2 + "px"
      span.style.top = e.clientY - r.top - size / 2 + "px"
      btn.appendChild(span)
      setTimeout(() => span.remove(), 700)
    })
  }

  /* ---------------- Back to top ---------------- */
  function initToTop() {
    const btn = document.getElementById("toTop")
    if (!btn) return
    window.addEventListener(
      "scroll",
      () => btn.classList.toggle("show", window.scrollY > 600),
      { passive: true },
    )
    btn.addEventListener("click", () =>
      window.scrollTo({ top: 0, behavior: "smooth" }),
    )
  }

  /* ---------------- Copy log ---------------- */
  function initCopy() {
    const btn = document.getElementById("copyLog")
    const log = document.getElementById("logText")
    if (!btn || !log) return
    btn.addEventListener("click", () => {
      const text = log.innerText
      const done = () => {
        btn.textContent = "Copied"
        setTimeout(() => (btn.textContent = "Copy"), 1800)
      }
      if (navigator.clipboard)
        navigator.clipboard.writeText(text).then(done).catch(done)
      else done()
    })
  }

  /* ---------------- Smooth anchor scroll ---------------- */
  function initSmoothScroll() {
    document.addEventListener("click", (e) => {
      const a = e.target.closest("a[href^='#']")
      if (!a) return
      const id = a.getAttribute("href")
      if (!id || id === "#") return
      const target = document.querySelector(id)
      if (!target) return
      e.preventDefault()
      target.scrollIntoView({ behavior: "smooth", block: "start" })
      history.replaceState(null, "", id)
    })
  }

  /* ---------------- Loader ---------------- */
  function initLoader() {
    const loader = document.getElementById("loader")
    if (!loader) return
    const hide = () => setTimeout(() => loader.classList.add("hidden"), 550)
    if (document.readyState === "complete") hide()
    else window.addEventListener("load", hide)
    setTimeout(() => loader.classList.add("hidden"), 3500)
  }

  /* ---------------- Boot ---------------- */
  function boot() {
    render()
    initNav()
    initTheme()
    initAccordion()
    initRipple()
    initToTop()
    initCopy()
    initSmoothScroll()
    initLoader()

    const y = document.getElementById("year")
    if (y) y.textContent = String(new Date().getFullYear())

    if (window.CleanWrapAnimations) window.CleanWrapAnimations.init()
    loadGithubStats()
  }

  if (document.readyState === "loading")
    document.addEventListener("DOMContentLoaded", boot)
  else boot()
})()
