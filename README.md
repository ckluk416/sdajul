# Program Hidrolisis Garam
ditujukan untuk memenuhi tugas mata kuliah struktur data dan algoritma

```mermaid
    flowchart TD
    A(["START"]) --> B["Load Data"]
    B --> B1["Read asam_list.txt, basa_list.txt"] & B2["Initialize Tree with Default Salts"] & C["Create Empty Stack & Queue"]
    C --> D{"Main Menu"}
    D -- "Combine Acid+Base" --> E["Select Acid from Array"]
    E --> F["Select Base from Array"]
    F --> G["Create New Salt Node in Tree"]
    D -- "Hydrolyze Salt" --> H["Select Salt from Tree"]
    H --> I["Display Acid/Base Components"]
    I --> J["Calculate pH"]
    J --> K["Push to History Stack"] & L["Enqueue to Process Queue"]
    D -- "Add New Acid/Base" --> M["Input Name, Ka/Kb"]
    M --> N["Append to asam_list/basa_list"]
    D -- "View History" --> O["Traverse Stack"]
    D -- "Undo" --> P["Pop Stack"]
    D -- "Exit" --> Q["Save Data to Files"]
    Q --> R(["END"])
    style A fill:#2ecc71,stroke:#27ae60
    style D fill:#3498db,stroke:#2980b9
    style R fill:#e74c3c,stroke:#c0392b
