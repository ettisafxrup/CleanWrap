#include "FileTypes.hpp"
namespace FileTypes
{
    const std::unordered_map<std::string, std::string> extensionMap = {

        // ___x____x___
        // Images
        // ___x____x___
        {".bmp", "Images"},
        {".jpg", "Images"},
        {".jpeg", "Images"},
        {".jpe", "Images"},
        {".jfif", "Images"},
        {".png", "Images"},
        {".gif", "Images"},
        {".bmp", "Images"},
        {".webp", "Images"},
        {".svg", "Images"},
        {".ico", "Images"},
        {".tif", "Images"},
        {".tiff", "Images"},
        {".heic", "Images"},
        {".heif", "Images"},
        {".avif", "Images"},
        {".raw", "Images"},
        {".cr2", "Images"},
        {".cr3", "Images"},
        {".nef", "Images"},
        {".arw", "Images"},
        {".dng", "Images"},
        {".orf", "Images"},
        {".rw2", "Images"},
        {".psd", "Images"},
        {".xcf", "Images"},

        // ___x____x___
        // PDFs
        // ___x____x___

        {".pdf", "PDFs"},

        // ___x____x___
        // Videos
        // ___x____x___

        {".mp4", "Videos"},
        {".mkv", "Videos"},
        {".avi", "Videos"},
        {".mov", "Videos"},
        {".wmv", "Videos"},
        {".flv", "Videos"},
        {".webm", "Videos"},
        {".m4v", "Videos"},
        {".3gp", "Videos"},
        {".3g2", "Videos"},
        {".3gp2", "Videos"},
        {".3gpp", "Videos"},
        {".3gpp2", "Videos"},
        {".asf", "Videos"},
        {".divx", "Videos"},
        {".dv", "Videos"},
        {".f4v", "Videos"},
        {".m2ts", "Videos"},
        {".mpeg", "Videos"},
        {".mpg", "Videos"},
        {".mts", "Videos"},
        {".ogv", "Videos"},
        {".rm", "Videos"},
        {".rmvb", "Videos"},
        {".swf", "Videos"},
        {".vob", "Videos"},

        // ___x____x___
        // Audio
        // ___x____x___

        {".mp3", "Audio"},
        {".wav", "Audio"},
        {".flac", "Audio"},
        {".aac", "Audio"},
        {".wma", "Audio"},
        {".m4a", "Audio"},
        {".ogg", "Audio"},
        {".oga", "Audio"},
        {".opus", "Audio"},
        {".mid", "Audio"},
        {".midi", "Audio"},
        {".mod", "Audio"},
        {".xm", "Audio"},
        {".s3m", "Audio"},
        {".it", "Audio"},
        {".669", "Audio"},
        {".amf", "Audio"},
        {".dsm", "Audio"},
        {".far", "Audio"},
        {".mdl", "Audio"},
        {".mtm", "Audio"},
        {".nst", "Audio"},
        {".ptm", "Audio"},
        {".sfx", "Audio"},
        {".ult", "Audio"},
        {".umx", "Audio"},
        {".voc", "Audio"},
        {".wpl", "Audio"},
        {".asx", "Audio"},
        {".m3u", "Audio"},
        {".m3u8", "Audio"},
        {".pls", "Audio"},
        {".cue", "Audio"},

        // ___x____x___
        // Source Code / Programming
        // ___x____x___

        {".c", "Code"},
        {".h", "Code"},
        {".cc", "Code"},
        {".cpp", "Code"},
        {".cxx", "Code"},
        {".hpp", "Code"},
        {".hxx", "Code"},
        {".py", "Code"},
        {".pyw", "Code"},
        {".java", "Code"},
        {".class", "Code"},
        {".js", "Code"},
        {".mjs", "Code"},
        {".cjs", "Code"},
        {".ts", "Code"},
        {".jsx", "Code"},
        {".tsx", "Code"},
        {".go", "Code"},
        {".rs", "Code"},
        {".cs", "Code"},
        {".csx", "Code"},
        {".php", "Code"},
        {".rb", "Code"},
        {".swift", "Code"},
        {".kt", "Code"},
        {".kts", "Code"},
        {".scala", "Code"},
        {".dart", "Code"},
        {".lua", "Code"},
        {".r", "Code"},
        {".m", "Code"},
        {".mm", "Code"},
        {".pl", "Code"},
        {".pm", "Code"},
        {".vb", "Code"},
        {".fs", "Code"},
        {".fsx", "Code"},
        {".sql", "Code"},
        {".html", "Code"},
        {".htm", "Code"},
        {".css", "Code"},
        {".scss", "Code"},
        {".sass", "Code"},
        {".less", "Code"},
        {".xml", "Code"},
        {".json", "Code"},
        {".yaml", "Code"},
        {".yml", "Code"},
        {".toml", "Code"},
        {".ini", "Code"},
        {".env", "Code"},
        {".sh", "Code"},
        {".bash", "Code"},
        {".zsh", "Code"},
        {".fish", "Code"},
        {".bat", "Code"},
        {".cmd", "Code"},
        {".ps1", "Code"},
        {".asm", "Code"},
        {".s", "Code"},
        {".sol", "Code"},
        {".graphql", "Code"},
        {".gql", "Code"},

        // ___x____x___
        // Executables / Installers
        // ___x____x___

        {".exe", "Executables and Installers"},
        {".msi", "Executables and Installers"},
        {".msix", "Executables and Installers"},
        {".appx", "Executables and Installers"},
        {".appxbundle", "Executables and Installers"},
        {".msixbundle", "Executables and Installers"},
        {".com", "Executables and Installers"},
        {".scr", "Executables and Installers"},
        {".dll", "Executables and Installers"},
        {".sys", "Executables and Installers"},
        {".ocx", "Executables and Installers"},

        // ___x____x___
        // Documents
        // ___x____x___

        {".doc", "Documents"},
        {".docx", "Documents"},
        {".docs", "Documents"},
        {".odt", "Documents"},
        {".rtf", "Documents"},
        {".txt", "Documents"},
        {".md", "Documents"},
        {".markdown", "Documents"},
        {".tex", "Documents"},
        {".pages", "Documents"},
        {".wpd", "Documents"},
        {".wps", "Documents"},
        {".log", "Documents"},
        {".bak", "Documents"},
        {".tmp", "Documents"},

        // ___x____x___
        // Presentations
        // ___x____x___

        {".ppt", "Presentations"},
        {".pptx", "Presentations"},
        {".pps", "Presentations"},
        {".ppsx", "Presentations"},
        {".pot", "Presentations"},
        {".potx", "Presentations"},
        {".odp", "Presentations"},
        {".key", "Presentations"},

        // ___x____x___
        // Spreadsheets
        // ___x____x___

        {".xls", "Spreadsheets"},
        {".xlsx", "Spreadsheets"},
        {".xlsm", "Spreadsheets"},
        {".xlsb", "Spreadsheets"},
        {".xlt", "Spreadsheets"},
        {".xltx", "Spreadsheets"},
        {".xltm", "Spreadsheets"},
        {".csv", "Spreadsheets"},
        {".tsv", "Spreadsheets"},
        {".ods", "Spreadsheets"},
        {".numbers", "Spreadsheets"},

        // ___x____x___
        // Ebooks / Digital Books
        // ___x____x___

        {".epub", "Ebooks"},
        {".mobi", "Ebooks"},
        {".azw", "Ebooks"},
        {".azw3", "Ebooks"},
        {".fb2", "Ebooks"},
        {".djvu", "Ebooks"},
        {".cbz", "Ebooks"},
        {".cbr", "Ebooks"},
        {".cb7", "Ebooks"},
        {".cba", "Ebooks"},
        {".cbt", "Ebooks"},

        // ___x____x___
        // Archives and Zips / Compressed Files
        // ___x____x___

        {".zip", "Archives and Zips"},
        {".rar", "Archives and Zips"},
        {".7z", "Archives and Zips"},
        {".tar", "Archives and Zips"},
        {".gz", "Archives and Zips"},
        {".tgz", "Archives and Zips"},
        {".bz2", "Archives and Zips"},
        {".xz", "Archives and Zips"},
        {".z", "Archives and Zips"},
        {".lz", "Archives and Zips"},
        {".lz4", "Archives and Zips"},
        {".zst", "Archives and Zips"},
        {".cab", "Archives and Zips"},
        {".arj", "Archives and Zips"},
        {".lzh", "Archives and Zips"},
        {".iso", "Archives and Zips"},
        {".img", "Archives and Zips"},
        {".dmg", "Archives and Zips"},
        {".jar", "Archives and Zips"},
        {".war", "Archives and Zips"},

        // ___x____x___
        // Fonts
        // ___x____x___

        {".ttf", "Fonts"},
        {".otf", "Fonts"},
        {".woff", "Fonts"},
        {".woff2", "Fonts"},
        {".eot", "Fonts"},

        // ___x____x___
        // Design / Graphics
        // ___x____x___

        {".ai", "Design"},
        {".eps", "Design"},
        {".indd", "Design"},
        {".xd", "Design"},
        {".sketch", "Design"},
        {".fig", "Design"},
        {".blend", "Design"},
        {".obj", "Design"},
        {".fbx", "Design"},
        {".3ds", "Design"},
        {".stl", "Design"},
        {".dae", "Design"},
        {".step", "Design"},
        {".stp", "Design"},
        {".iges", "Design"},
        {".igs", "Design"},

        // ___x____x___
        // CAD / Engineering
        // ___x____x___

        {".dwg", "CAD"},
        {".dxf", "CAD"},
        {".sldprt", "CAD"},
        {".sldasm", "CAD"},
        {".slddrw", "CAD"},
        {".ipt", "CAD"},
        {".iam", "CAD"},
        {".idw", "CAD"},
        {".catpart", "CAD"},
        {".catproduct", "CAD"},
        {".catdrawing", "CAD"},

        // ___x____x___
        // Data / Databases
        // ___x____x___

        {".db", "Data"},
        {".sqlite", "Data"},
        {".sqlite3", "Data"},
        {".mdb", "Data"},
        {".accdb", "Data"},
        {".parquet", "Data"},
        {".avro", "Data"},
        {".jsonl", "Data"},

        // ___x____x___
        // Subtitles / Captions
        // ___x____x___

        {".srt", "Subtitles"},
        {".ass", "Subtitles"},
        {".ssa", "Subtitles"},
        {".sub", "Subtitles"},
        {".vtt", "Subtitles"},
        {".sbv", "Subtitles"},

        // ___x____x___
        // Disk Images / Virtual Machines
        // ___x____x___

        {".vdi", "Virtual Machines"},
        {".vmdk", "Virtual Machines"},
        {".vhd", "Virtual Machines"},
        {".vhdx", "Virtual Machines"},
        {".ova", "Virtual Machines"},
        {".ovf", "Virtual Machines"},

        // ___x____x___
        // Certificates / Security
        // ___x____x___

        {".cer", "Certificates"},
        {".crt", "Certificates"},
        {".pem", "Certificates"},
        {".der", "Certificates"},
        {".p12", "Certificates"},
        {".pfx", "Certificates"},

        // ___x____x___
        // Playlists
        // ___x____x___

        {".m3u", "Playlists"},
        {".m3u8", "Playlists"},
        {".pls", "Playlists"},
        {".wpl", "Playlists"},

        // ___x____x___
        // Torrent Files
        // ___x____x___

        {".torrent", "Torrents"}};

    const std::string &getCategory(const std::string &extension)
    {
        static const std::string others = "Others";

        auto it = extensionMap.find(extension);
        return it == extensionMap.end() ? others : it->second;
    }
}
