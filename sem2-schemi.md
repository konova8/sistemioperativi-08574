# Sistema Operativo

Un **Sistema operativo** è livello di astrazione:
- Realizza il concetto di processo
- Il "linguaggio" fornito dal SO è definito dalle system call
- Implementato tramite un programma che **controlla l'esecuzione di programmi applicativi** e agisce come **interfaccia tra le applicazioni e l'hardware** del calcolatore

Gli **obbiettivi** sono ottenere *Efficienza* e *Semplicità*

Un sistema operativo nasconde i dettagli dell'hardware ai programmatori tramite una API che agisce come intermediario.

Servizi estesi offerti da un SO (classi di System Call):
- Esecuzione dei programmi
- Accesso ai dispositivi I/O
- Accesso a File System
- Accesso a networking
- Accesso al sistema
- Rilevazione e risposta agli errori
- Accounting (Come gestione di timer, utilizzo di memoria, ecc)

## Storia dei Sistemi Operativi

- **Generazione 1**: 1945 - 1955
	- Valvole e tavole di commutazione
- **Generazione 2**: 1955 - 1965
	- Transistor e Sistemi Batch
- **Generazione 3**: 1965 - 1980
	- Circuiti integrati, multiprogrammazione e time-sharing
- **Generazione 4**: 1980 - oggi
	- Personal Computer

### Generazione 0
**Babbage (1792-1871)**
- Macchina programmabile e meccanica
- Niente SO

### Generazione 1
- Macchine a valvole e tavole di commutazione
- Solo calcoli numerici, gruppi di persone per singolo computer
- Venivano programmati direttamente in linguaggio macchina
- Ovviamente nessun SO

Problemi:
- Guasti frequenti
- Utilizzazione lenta e complessa

### Generazione 2
- Iniziano ad essere usati i transistor
- Più economici e più affidabili
- Iniziano quindi ad avere mercato e ad affermarsi
- Programmazione in Assembly e Fortran, tramite schede perforate
- Sistema operativo "batch"

Definizione: **JOB**
- Un programma o un insieme di essi la cui esecuzione veniva richiesta da uno degli utenti del computer

Ciclo di esecuzione di un job:
- Il programmatore scrive il programma su carta, perfora le schede e consegna le schede all'operatore
- L'operatore inserisce le schede di controllo, poi quelle del programma, attente il risultato e lo consegna al progammatore

Primi rudimentali esempi di SO, detti anche *monitor residenti*
- Controllo iniziale del monitor
- Controllo ceduto al job corrente
- Terminato, il job resituisce il controllo al monitor

**Sistema batch** = "infornata"

Problemi:
- Molte risorse inutilizziate, il passaggio da un job ad un altro rende parte del processore inutlizzato
- Primo miglioramento caricando i job su un nastro (off-line), elaborazione con output sul nastro ed infine stampa sul nastro di output (off-line)

### Generazione 3
Utilizzo di circuiti integrati, ci si sposta ad un utente come operatore

Venivano programmati in C, si usavano editor testuali, compilatori. Si aveva accesso al sistema da terminali

Sistemi operativi **interattivi**, **multi-programmazione** e **time sharing**

- **Multi-programmazione**
	- Utilizzare il processo durante i periodi di I/O di un job per eseguire altri job
	- Il vantaggio è lo sfruttamento totale del processore in caso di operazioni I/O lunghe, oltre all'utilizzo migliore di memoria
	- Caratteristiche dei SO multiprogrammati
		- Le routine di I/O devono essere fornite dal SO
		- Gestione della memoria come stack
		- CPU scheduling, il SO sceglie quale job eseguire
		- Allocazione delle risorse di I/O
- **Time sharing**
	- Estensione logica della multi-programmazione
	- Esecuzione della CPU divisa in $n$ *quanti* temporali
	- Allo scadere di un *quanto*, si passa ad un altro job (anche in assenza di richieste di I/O
	- I passaggi (*context switch*) avvengono così frequentemente che più utenti possono interagire con i programmi in esecuzione
	- Caratteristiche dei SO time sharing
		- Gestione della memoria come memoria virtuale
		- CPU scheduling di tipo *preemptive* e *time-sliced*
		- Meccanismi di protezione per utilizzo multi utente

Unix era la riscrittura in C dei SO scritti in Assembly

### Generazione 4
Personal computer dedicati ai singoli utenti, con l'obbiettivo primario della facilità d'uso

Sottovalutazione della sicurezza, solo dopo i SO dei PC furono resi sicuri

## Sistemi paralleli
Un singolo elaboratore che possiede più unità di elaborazione

Due tipi: **SIMD** (Single Instruction, Multiple Data) e **MIMD** (Multiple Instruction, Multiple Data)

- Sistemi **tightly** coupled
	- Bus / Memoria condivisa
	- Pochi processi / Basso livello di parallelismo. Bus = bottleneck
- Sistemi **loosely** coupled
	- Processori con memoria privata interconnessi da canali
	- Tanto processori, alto livello di parallelismo

- Symmetric multiprocessing (SMP)
	- Ogni processore esegue una copia identica del SO
	- Processi diversi eseguibili contemporaneamente
	- Molti SO supportano SMP
- Asymmetric multiprocessing
	- Ogni processore è assegnato ad un compito specifico, un processore master gestisce l'allocazione
	- Comune in sistemi molto grandi

## Sistemi distribuiti
Sistemi composti da più elaboratori indipendenti. Esempio: Macchine di laboratorio

- Condivisione di file
- Possibilità di comunicare
- Ogni computer opera in modo indipendente
- Minore utonomia tra computer
- Dà l'impressione che un singolo SO stia controllando tutti gli elaboratoridi sistema distribuito

## Sistemi real-time
Sistemi per cui la correttezza del risultato dipende anche dall'istante nel quale il risultato viene prodoto

I sistemi real-time si dividono in:
- hard real-time
	- Se il mancato rispetto dei vincoli temporali può avere effetti catastrofici
- soft real-time
	- Se si hanno solamente disagi o disservizi

NB: real-time non significa necessariamente esecuzione veloce

