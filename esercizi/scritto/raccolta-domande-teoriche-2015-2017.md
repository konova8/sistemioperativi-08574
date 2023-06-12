# 2017/02/09
## Esercizio g.1:
Una partizione contiene un file systems ext2. Nella directory radice all’interno della partizione ci sono tre directory: una chiamata
“lost+found” (quella standard per il controllo di coerenza), una seconda chiamata “dev” ed una terza “dir”.
La directory “dev” contiene un file speciale a caratteri denominato “null” che ha major number 1 e minor number 3.
La directory “dir” contiene:
* “null.phy” che è un link fisico al file “null” della directory “dev”.
* “null.sym” è un link simbolico che punta a “../dev/null”.
La directory “lost+found” è vuota.
Spiegare come funziona il file system di tipo ext2 e mostrare il contenuto di tutte le strutture dati relative al caso qui illustrato.

## Esercizio g.2: 
1) Usando un file system con journaling anche se un sistema viene spento senza fare la procedura di shutdown non si perdono dati.
	- Falso, il journaling È UN SISTEMA PER CONTROLLARE LA COERENZA NEI FILE MA NON PER RECUPERARE O PROTEGGERE I DATI.

2) La crittografia a chiave pubblica (doppia chiave) puo’ essere usata al posto di quella a singola chiave e quindi quest’ultima sta cadendo in disuso.
	- Falso, la crittografia a chiave pubblica e' molto piu' costosa di quella a chiave singola, quindi solitamente viene usata solo in alcuni casi

3) Gli scheduler a priorita’ sono particolarmente indicati per i programmi interattivi
	- Vero, sono particolarmente indicati perchè sono scheduler che cambiano dinamicamente in base agli input ricevuti a livello utente, se assegnamo una priorita' piu' alta ai processi interattivi il sistema sembrera' avere meno latenza

4) Il problema del deadlock puo’ essere risolto con tecniche di checkpointing & rollback.
	- Vero, nel caso si entri in deadlock tramite la tecnica di checkpointing, ovvero il salvataggio dello stato dei processi, e di roolback, azione di ripristinare i processi al loro precedente stato finche non è più presente deadlock, si può risolvere lo stato di stallo.

5) Deadlock prevention e avoidance sono la stessa cosa.
	- Falso, prevention consiste nell'eliminare uno dei 4 casi che causano deadlock strutturalmente, ma cio' pone dei limiti alla multiprocessabilita', avoidance invece è l'attribuzione di risorse in stato SAFE nel quale abbiamo la certezza che in futuro non possa avvenire deadlock (Vedi algoritmo del banchiere).

# 2017/06/19
## g.2
1) perché aumentando la dimensione dell’area di memoria secondaria usata dalla memoria virtuale si corre rischio di trashing?
	- Piu' e' grande il frame buffer piu' abbiamo il rischio che ci siano processi attivi che tendono a rubarsi le pagine a vicenda

2) cosa provoca la scelta errata della durata del quanto di tempo in uno scheduler round robin?
	- Se il quanto di tempo è troppo piccolo il sistema risulta inefficiente perchè c'è un continuo scambio di processi, se troppo grande il sistema non avra' la reattivita' voluta
	- Infatti solitamente lo scheduler Round Robin viene usato lasciando una priorita' piu' alta ai processi piu' interattivi

# 2017/05/29
2) Perché è necessario usare spinlock in sistemi multiprocessore per implementare kernel di tipo simmetrico (SMP)?
	- perchè è necessario un sistema di sincronizzazione tra i processori che gestica gli accessi alle aree di memoria in comune.

3) Perché nei sistemi reali l’algoritmo di rimpiazzamento second chance (orologio) viene preferito a LRU sebbene il primo non sia a stack e il secondo sì?
	- second chance è un'approssimazione di LRU in quanto quest'ultimo non è possibile usarlo a causa dell'alto consumo hardware dovuto al continuo aggiornamento del counter, mentre second chance è un'implementazione che va a verificare se la pagina è già stata acceduta e quindi ha il reference bit a 1 oppure a 0 e in quest'ultimo caso viene scelta questa come vittima.

4) Perché revocare un’autorizzazione espressa come capability è più difficile che revocare lo stesso diritto quando espresso come access control list?
	- Perchè il sistema di autenticazione con ACL è un sistema che si può definire "centralizzato", poichè il sistema operativo deve controllare ogni volta se il richiedente ha i permessi di utilizzo di un oggetto, mentre con le capability le autorizzazioni sono in mano al processo stesso, quindi la revoca puo' avvenire in vari modi (come assegnare un timer alla capability, che poi dovra' tornare a chiedere l'autorizzazione al kernel)

# 2016/05/30
1) A cosa serve il processo IDLE (che mette il processore in wait state se possibile o esegue un loop infinito)? Quando viene messo in esecuzione? Come si gestisce l’attivazione di IDLE negli scheduler a priorità e nel round-robin?
	- Quando non vi sono presenti processi schedulati nel processore viene inserito il processo IDLE che mette il processore in wait state.
	- Negli scheduler a priorità e a round-robin se non sono preseti processi in ready queue che aspettano di essere consegnati alla cpu oppure quando aspettano di entrare in I/O, se la cpu è libera viene inserito il processo IDLE

2) Lo stato unsafe è condizione necessaria ma non sufficiente perché possa verificarsi deadlock. Quali sono I passi logici necessari per dimostrare questa affermazione?
	- Lo stato UNSAFE indica che se un processo dovesse richiedere al momento "sbagliato" le risorse questo potrebbe generare deadlock, ma non e' una situazione certa
	- Con l'algoritmo del banchiere (deadlock avoidance) non eliminiamo strutturalmente il deadlock, ma nel caso all'assegnamento di una risorsa si passasse ad uno stato UNSAFE il processo viene messo in coda e attende che sia disponibile la risorsa in quantita' sufficiente per lasciare lo stato del sistema SAFE

3. Quali metodi di allocazione per file system ammettono la creazione di file di grandezza arbitrario?
	- Un'allocazione concatenata senza blocchi permette la creazione di file di grandezza arbitararia, se abbiamo bisogno dei blocchi possiamo usare anche un'allocazione a blocchi con lista concatenata
	- Non possiamo usare sistemi come quello UNIX, dove i blocchi utilizzati per un file sono indicizzati, quindi la dimensione massima e' la grandezza del blocco che contiene l'elenco degli indici

4. Perché per utilizzare le capability come strumento di autorizzazione è sufficiente usare un metodo crittografico a singola chiave?
	- Perchè una volta utilizzata la chiave singola come mezzo di autenticazione, solo il processo avente la capability avrà la possibilità di interagire con l'oggetto tramite i permessi forniti dalla capability.
	- TODO da controllare

# 2018/09/19
1. Perché per realizzare un servizio di memoria virtuale l'algoritmo di rimpiazzamento LRU è difficile da implementare?
	- Perchè l'algoritmo deve tenere traccia tramite un contatore temporale dell'ultima pagina acceduta, si implementa utilizzando uno stack di pagine, dove la pagina acceduta più recentemente è in cima e quella meno recentemente in basso.
	- I contatori devono essere memorizzati in memoria e questo richiede accessi addizionali alla memoria.

2. In quali casi anche utilizzando file system con supporto di journaling si possono perdere informazioni?
	- Nei casi in cui il processo sta scrivendo in memoria i dati e venga interrotto e non completi tutte le operazioni che sta eseguendo, un esempio classico può essere la caduta di tensione del sistema. Il journaling è un sistema di controllo della coerenza non evita la perdita di dati.

3. Perché il servizio di message passing asincrono e quello sincrono non hanno lo stesso potere espressivo?
	- Nel message passing sincrono il processo che esegue la ssend() non si blocca in attesa che il processo ricevente esegua la sreceive().
	- Nel message passing asincrono invece la asend() non è bloccante, mentre come nel caso del sincorno la areceive() rimane bloccante, cioè si blocca in attesa che il mittente esegua la send().
	
4. esistono processori che non hanno istruzioni privilegiate (modo kernel/modo user). Quali conseguenze ci sono per i sistemi
operativi?
	- Si, esistono. I processori a istruzioni privilegiate sono stati pensati come metodo di protezione, senza istruzioni privilegiate l'utente eseguendo codice può interagire direttamente con l'hardware del sistema, un errore nel codice può portare ad eventi catastrofici sull'hardware.

# 2018/07/17
1. In quali casi è bene non usare la memoria virtuale?
	- In sistemi dove si un hardware molto limitato, infatti l'utilizzo della memoria virtuale ha molteplici vantaggi, ma a scapito delle prestazioni. Se prendiamo in esame un sistema embedded infatti le sue caratteristiche generalmente non sopportano la gestione della memoria virtuale, essendo stati progettati per eseguire operazioni dal "costo" contenuto.

2. Perché il file system FAT viene ancora utilizzato?
	- FAT32 può essere ancor'oggi la scelta giusta per formattare un'unità USB che deve essere leggibile da quanti più dispositivi possibile (il file system FAT32 è compatibile con tutti i device, con tutte le varie versioni di Windows, Mac OS X e Linux ed in generale con qualunque dispositivo sia dotato di una porta USB).
	- È altamente sconsigliato usare FAT32 per le unità disco "interne" perché il file system manca della gestione dei permessi e di tutta una serie di funzionalità di sicurezza che sono ad esempio proprie del più moderno NTFS.
	- FAT32 può essere quindi ancora la scelta giusta per formattare le chiavette USB a patto ovviamente di non avere file di dimensioni superiori ai 4 GB da memorizzarvi.

3. A cosa serve gestire batterie di dischi con metodologia RAID? E’ necessario fare backup dei dati memorizzati in RAID?
	- Serve per poter velocizzare il tempo di accesso ai dischi, utilizzando RAID è possibile scrivere/leggere contemporaneamente mentre utilizzando un disco solo dobbiamo eseguire un operazione alla volta.
	- RAID serve anche per proteggere il sistema dalla perdita di dati, in base a che livello di RAID usiamo possiamo proteggere il sistema a dispetto della velocità.
	- Un RAID6 sarà più lento di un RAID0 però potrà proteggere il sistema dalla perdita di dati anche se avverrànno guasti di 2 differenti dischi(al massimo).

4. Dimostrare che un ciclo in un grafo di Holt multirisorsa non è condizione sufficiente perché ci sia un deadlock.
	- La condizione sufficiente e' quella che ci sia un KNOT, ovvero un sottoinsieme di nodi da cui se si parte da uno si arriva a tutti e solo gli altri del KNOT
	- Il ciclo non e' condizione sufficiente, perche' se ho un ciclo ma un processo all'interno puo' terminare allora il ciclo si "risolve"

2018/06/21
1. A cosa serve e quando viene eseguito l'algoritmo di calcolo del working set?
	- L'algoritmo del working set calcola una approssimazione delle pagine più "utili" ai processi e che quindi durante l'esecuzione dell'algoritmo di gestione del page fault non dovranno essere sostituite per evitare trashing.

2. Come si calcola la lunghezza massima di un file che si può memorizzare su un file system di tipo fat?
	-  Lo spazio massimo di memorizzazione consiste in quanti bit sono allocati per numerare i cluster del disco.
	- Con 12 bit, il file system può indirizzare al massimo 2^12 = 4096 cluster, mentre con 32 bit si possono gestire 2^32 = 4.294.967.296 cluster; l'aumento del numero di bit di indirizzo dei cluster si è reso necessario per gestire unità a disco sempre più grandi e capienti.

3. Quali sono le differenze fra un virus e un worm? come ci si difende da questi tipi di malware?
	- Un worm è simile a un virus, del quale può essere considerato una sottocategoria. I worm si diffondono da computer a computer, ma diversamente da un virus, hanno la capacità di viaggiare senza l'aiuto di una persona.
	- I virus sono programmi che modificano altri programmi non maligni già esistenti.
	- I worm sono programmi che diffondono copie di sè stessi nella rete.
	- Non eseguire codice non considerato trust, mantenere il sistema operativo e l'antivirus aggiornati, fare attenzione ai file che si scaricano dal web e i messaggi che si ricevono via mail, dato che il metodo di riproduzione più usato dai malware è proprio tramite e-mail.

4. In quali casi la ready queue di uno scheduler può essere vuota? Sono casi fisiologici o patologici della vita di un sistema?
	- Quando tutti i processi stanno facendo I/O ed è fisiologico.


# 2018/05/28
1. A cosa serve e quando viene eseguito un algoritmo di rimpiazzamento?
	- Viene eseguito quando avviene un page fault nella memeoria ed è necessario liberare un frame della memoria pricipale e caricare quello utile dalla memoria secondaria.

2. Come si calcola la lunghezza massima di un file che si può memorizzare su un file system di tipo ext2?
	- è un tipo di allocazione indicizzata, la dimensione massima del blocco indice determina la dimensione massima del file.

3. A cosa serve il meccanismo del sale (salt) nella memorizzazione delle password criptate? E se il salt funziona, perché le password criptate in Linux vengono memorizzate nel file "/etc/shadow" e non in "/etc/passwd"?
	- Per salvare le password una volta si utilizzava un metodo di codificazione con una funzione one-way, ma se veniva utilizzato un attacco dizionario utilizzando un dizionario codificato nella stessa maniera sussisteva un problema di sicurezza.
	- Venne introdotto il meccanismo si salt, prevedava l'aggiunta di un numero casuale durante la codifica per aumentare di molto il numero di combinazioni da inserire nel dizionario per poter crackare la password.
	- Il problema che un tempo si era incontrato era che l'accesso a /etc/passwd era libero, si è quindi modificata la memorizazzione delle password in /etc/shadow poichè solo il root ha la possibilità di accedevi.

4. Cosa occorre fare per evitare il deadlock quando lo stato calcolato dall'algoritmo del banchiere risulta unsafe?
	- Il deadlock avviene quando nello stesso momento vi è: attesa circolare, mutua esclusione, impossibilità di prelazione, accumulo incrementale. Quando l'algoritmo del banchiere risulta unsafe bisogna predisporre l'ordine di esecuzione dei processi in modo tale che tutti i processi nell'attimo dell'esecuzione abbiano le risorse necessarie per essere eseguite.

# 2018/02/12
1. Quando viene richiamato l'algoritmo del Banchiere e cosa succede se lo stato risultante viene valutato unsafe (non safe)?
	- Quando l'algoritmo del banchiere risulta unsafe bisogna predisporre l'ordine di esecuzione dei processi in modo tale che tutti i processi nell'attimo dell'esecuzione abbiano le risorse necessarie per essere eseguite.

2. Quali contromisure sono necessarie quando la somma dei working set dei processi attivi supera il numero di frame della memoria
presenti in un sistema che adotta allocazione globale della memoria primaria?
	- Bisogna ricalcolare l'ampiezza delle finestre del working set dei processi attivi poichè se no il sistema è in trashing.
Il sistema impiegherà più tempo ad eseguire l'algoritmo di rimpiazzamento che ad eseguire effettivamente i processi.

3. RAID 1 e RAID 5 tollerano entrambi il guasto di un solo disco. Quando è indicato usare RAID 1 e quando RAID 5?
	- In RAID1 vi è una copia speculare dei dati del disco su un'altro disco, mentre su RAID5 i dati vengono divisi su tutti i dischi nel cluster e viene calcolato un bit di parità per la correzzione degli errori, tutto ciò distribuito nei vari dischi.
	- RAID5 ha una capacità di memorizzazione più grande rispetto a RAID1, ma è molto più lento, però offre protezione dei dati e ridondanza con il malfuzionamento di un disco solo.

4. Il tempo rimanente calcolato dall'algoritmo SRTF può diventare negativo? (sì o no, perché?)
	- ???


# 2018/01/22
1. A cosa serve partizionare un disco? Fornire esempi pratici di uso di dischi partizionati.
	- Il partizionamento di un disco è utilizzato spesso per poter avere disponibili nello stesso sistema diversi file system indipendenti.
	- Un computer può ospitare nello stesso disco, in partizioni separate, diversi sistemi operativi, ovviamente che non possono essere eseguiti nello stesso momento

2. Quale è la differenza fra TLB miss e page fault nella gestione della memoria virtuale?
	- La TLB la si può pensare come una cache della Page Table, è un suo sottoinsieme, viene utilizzata per velocizzare la mappatura degli indirizzi virtuali in indirizzi fisici.

3. Fornire esempi di file system con allocazione contigua, e spiegare perché sarebbe inefficiente usare altri metodi di allocazione nei casi d'uso tipici di questi file system.
	- ???

4. Come funziona la tecnica denominata aging e come riesce ad evitare la starvation negli scheduler a priorità?
	- La tecnica aging consiste nel assegnare una priorità ai processi, gradualmente ogni processo si vedrà incrementata la priorità, in questa maniera anche i processi che all'inizio avevano una bassa priorità ad un certo punto avranno priorità alta e verranno eseguiti, evitando così di rimanere per sempre a priorità bassa e non eseguiti mai.

# 2017/09/11
1. Per I file system di tipo fat non è efficiente l'accesso diretto (ad esempio con la system call lseek) a file di grandi dimensioni.Perché?
	- La scansione richiede la lettura anche della FAT. La FAT è una tabella esterna al file dove si trovano i puntatori ai blocchi sucessivi del file.

2. È necessario il supporto DMA per implementare un device driver di tipo interrupt driven? Perché?
	- ???

3. A cosa serve gestire batterie di dischi con metodologia RAID? E’ necessario fare backup dei dati memorizzati in RAID?
	- RAID è molto utile poichè si riesce a velocizzare di molto l'accesso ai dischi e di conseguenza, lettua e scrittura.
	- È ulizzato allo stesso tempo come protezione dei dati, in base al tipo di RAID utilizzato la sicurezza è differente, ma se prendiamo in esame il RAID6, può avvenire un guasto su di un massimo  di 2 differenti dischi e non perdere nessuna informazione.

4. Quali sono i benefici del linking dinamico?
	- Vi è un risparmio di memoria dato che il link delle routine di libreria è effettuato solo al momento del primo riferimento durante l'esecuzione.

# 2017/07/17
1. La ricostruzione della coerenza mediante tecnica di journaling risolve solo alcuni tipi di incoerenze, quali non vengono gestite?
	- ???

2. Applicando la paginazione con la segmentazione aumenta la frammentazione interna (rispetto alla paginazione senza segmentazione). Questa affermazione è vera o falsa, perché? 
	- ???

3. Quale è la differenza fra gli algoritmi di scheduling “Shortest Time First” e “Shortest Remaining Time First”?
	- ???

4. Perché il meccanismo del “sale” (salt) rende più complesso l’attacco di tipo dizionario alle password?
	- Perchè nel momento della codifica della password viene aggiunto un numero randomico nell'hash, in questa maniera il numero di combinazioni che devono essere presenti all'interno del dizionario utilizzato per l'attacco è molto più elevato.

# 2017/06/19
1. perché aumentando la dimensione dell’area di memoria secondaria usata dalla memoria virtuale si corre rischio di trashing?
	- ???

2. cosa provoca la scelta errata della durata del quanto di tempo in uno scheduler round robin?
	- se il quanto è troppo breve potremmo rallentare l'esecuzione dei processi poichè ci saranno troppi salti di esecuzione tra un processo e l'altro, mentre se troppo grande avremo dei periodi di inattività dei processi.

4. quali sono le condizioni necessarie per poter applicare l’algoritmo del banchiere
	- Conoscere la quantità di risorse che abbiamo disponibili, e la quantità di risorse necessarie ad ogni processo per poter essere eseguito

5. quali sono i vantaggi di usare una FAT rispetto ad una allocazione concatenata dove l’indirizzo del prossimo blocco dati viene memorizzato nel blocco dati stesso?
	- ???


# 2017/05/29
1. Un i-node di un file system tipo ext2 per un errore viene riportato un numero di link maggiore del reale. Cosa può succedere se si continua ad usare il file system? (perché?) E se il numero di link errato fosse al contrario inferiore al reale cosa potrebbe succedere? (perché?)
	- ???

2. Perché è necessario usare spinlock in sistemi multiprocessore per implementare kernel di tipo simmetrico (SMP)?
	- ???

3. Perché nei sistemi reali l’algoritmo di rimpiazzamento second chance (orologio) viene preferito a LRU sebbene il primo non sia a stack e il secondo sì?
	- ???

4. Perché revocare un’autorizzazione espressa come capability è più difficile che revocare lo stesso diritto quando espresso come access control list?
	- ???

# 2017/02/09
1. Perché uno scheduler non-preemptive non è adatto per processi interattivi?
	- perchè se qualcun'altro è in I/O in quel momento, sarà quel processo a decidere quando rilasciare la risorsa e l'utente rimarrà in attesa

2. Quando è sconsigliato usare un meccanismo di protezione di accesso di tipo Access Control List?
	-  Nel caso in cui avessi un sistema con tantissimi utenti e con permessi diversi è meglio utilizzare capability(rilasciare un token momentaneo) piuttosto che continure ad aggiungere informazione al file ACL che diverrebbe enorme infatti ACL molto grandi riducono le performance

3. Perché l’algoritmo di rimpiazzamento LRU non viene in pratica utilizzato nell’implementazione della memoria virtuale?
	- Occorre molto supporto hardware, i continui aggiornamenti del marcatore temporale causano un continuo rimoscolio delle pagine e l'impossibilità di determinare la pagina da sostituire.
	- Viene aggiornato in continuazione il marcatore temporale e per questo abbiamo un alto utilizzo hardware.

4. Dati N dischi aventi le stesse caratteristiche, il tempo medio di accesso è minore se creiamo con essi un cluster RAID0 o uno RAID5?
Stimare la perdita di prestazione del più lento rispetto al più veloce.
	- RAID0 È IL PIÙ VELOCE, perchè l'accesso ai dati avviene in parallelo sui dischi e quindi vengono effettuate più richieste I/O nello stesso momento.
	- Il RAID 5 al contempo è più sicuro poichè contiene all'interno dei bit di parità che se avviene un errore CRC il disco può eseguire un controllo e verificare l'integrità dei dati e un conseguente leggero rallentamento delle prestazioni del sistema.
	- Lo svantaggio del RAID5 è che il disco deve ciclicamente calcolare e aggiornare gli strip di parità tutte le volte che viene un accesso in scrittura ai dati.
		```
		Raid 0
		r = 1/n
		w = 1/n
		Raid 5
		r = 1/n-1
		w = 1/1
		```



# 2017.01.18
1. Perché un algoritmo di rimpiazzamento a stack non soffre dell’anomalia di Belady?
	- ???

2. Perché si può usare un meccanismo di crittografia simmetrica nella gestione delle capability di accesso alle risorse?
	- ???

3. Quali operazioni svolge il processore per la gestione di un interrupt e quali invece sono a carico del kernel del sistema operativo?
	- ???

4. Perche’ il mascheramento degli interrupt non si può utilizzare per creare sezioni critiche in sistemi multicore o multiprocessore?
	- ???

5. Per quali tipi di processo l’algoritmo di schedulazione round-robin è efficiente e per quali no?
	- ???


# 2016.09.15
1. Cosa sono gli spinlock e quale ruolo hanno nell’implementazione di kernel per sistemi multiprocessore (in modalita’ simmetrica SMP).
	- ???

2. Cosa e’ il Translation Lookahead Buffer (TLB) presente nelle MMU moderne e quale e’ il ruolo del TLB nella gestione della memoria
virtuale mediante paginazione a richiesta.
	- ???

3. Quale e’ la differenza fra una funzione di una libreria ed una system call? In altre parole, perche’ sono necessarie le system call?
	- ???

4. RAID1 consente di aumentare le prestazioni per le operazioni di lettura ma non per quelle di scrittura. E’ una affermazione vera o
falsa? Perche’?
	- ???

# 2016/07/27
1. Usando un file system con journaling anche se un sistema viene spento senza fare la procedura di shutdown non si perdono
dati.
	- ???

2. La crittografia a chiave pubblica (doppia chiave) puo’ essere usata al posto di quella a singola chiave e quindi quest’ultima sta cadendo in disuso.
	- No

3. Gli scheduler a priorita’ sono particolarmente indicati per i programmi interattivi.
	- ???

4. Il problema del deadlock puo’ essere risolto con tecniche di checkpointing & rollback.
	- ???

5. Deadlock prevention e avoidance sono la stessa cosa.
	- ???


# 2016/05/30
1. A cosa serve il processo IDLE (che mette il processore in wait state se possibile o esegue un loop infinito)? Quando viene messo in esecuzione? Come si gestisce l’attivazione di IDLE negli scheduler a priorità e nel round-robin?
	- ???

2. Lo stato unsafe è condizione necessaria ma non sufficiente perché possa verificarsi deadlock. Quali sono I passi logici necessari per dimostrare questa affermazione?
	- ???

3. Quali metodi di allocazione per file system ammettono la creazione di file di grandezza arbitrario?
	- ???

4. Perché per utilizzare le capability come strumento di autorizzazione è sufficiente usare un metodo crittografico a singola chiave?
	- ???

# 2016/02/10
1. Se un sistema ha una RAM molto ampia puo' non essere utile usare la memoria virtuale. In questo caso ha senso egualmente usare la paginazione di memoria? Perche'?
	- ???

2. Confrontare gli algoritmi di scheduling round robin e a priorita' statica. Indicare in quali casi sono da usare algoritmi di tipo round robin e quando quelli a priorita' statica.
	- ???

3. Lo stato unsafe e' condizione necessaria ma non sufficiente perche' possa verificarsi deadlock. Quali sono I passi logici necessari per dimostrare questa affermazione?
	- ???

4. In quali casi si usano ancora oggi I file system con metodo di allocazione contigua?
	- ???

# 2016/01/21
1. Quali sono i casi di frammentazione interna ed esterna che possono avvenire usando la paginazione.
	- ???

2. Per I file system di tipo fat non e' efficiente l'accesso diretto (ad esempio con la system call lseek) a file di grandi dimensioni. Perche'?
	- ???

3. Per quali tipi di processo e' indicato uno schedule a priorita' statica? Quale problema puo' essere causato da uno scheduler a priorita' statica? perche'?
	- ???

4. Cosa e' un knot in un grafo? Quale teorema lega la definizione di knot in un grafo e la presenza di deadlock fra processi?
	- ???

# 2015/09/14
1. In quali casi si usano ancora oggi I file system con metodo di allocazione contigua?
	- ???

2. Come viene usato l'algoritmo della media esponenziale nello scheduler shortest job first? La media esponenziale dipende da un parametro (normalmente indicato con alpha, di valore fra zero e uno). A cosa serve questo parametro?
	- ???

3. Lo stato unsafe e' condizione necessaria ma non sufficiente perche' possa verificarsi deadlock. Quali sono I passi logici necessari per dimostrare questa affermazione?
	- ???

4. Due sistemi gestiscono file system di grandi dimensioni (per es. 10 Terabyte di dati). Il primo usa file system di tipo ext2, il secondo di tipo ext3. Per un guasto al gruppo di continuita' entrambi i sistemi vengono spenti senza un appropriato shutdown. Cosa cambia alla riaccensione? Perche'?
	- ???

# 2015/07/29
1. Dimostrare che in un grafo di Holt multirisorsa (relativo a classi di risorse seriali, non prerilasciabili e non condivisibili) la
presenza di un ciclo e' necessaria ma non sufficiente perche' ci sia un deadlock.
	- ???

2. L'algoritmo di rimpiazzamento “Second Chance”, chiamato anche “dell'orologio” e' a stack? Perche'?
	- ???

3. Se N dischi formano un sistema RAID 5, a quanti dischi occorre accedere per leggere un blocco e a quanti dischi occorre accedere per scrivere un blocco (quando il sistema e' in perfetta efficienza)? E se uno dei dischi si guasta, a quanti dischi occorre accedere per leggere un blocco?
	- ???

4. Usando file system di tipo con gestione del Journal (es. ext3/ext4), c'e' la certezza di non perdere dati anche se un sistema viene spento in modo improprio?
	- ???

# 2015/06/17
1. Il fenomeno del Trashing dipende dal tipo di algoritmo di rimpiazzamento utilizzato? Perche'?
	- ???

2. Quando l'algoritmo di scheduling della memoria secondaria C-LOOK e' preferibile a LOOK (ascensore)?
	- ???

3. Indicare e spiegare (almeno) tre tipi di controllo di coerenza svolti da fsck.
	- ???

4. Come si puo' revocare un diritto di accesso fornito tramite capability?
	- Si in 3 modi principalmente:
		1) cancellando l'utente,
		2) creando una nuova login per quell'utente e creando nel nuovo account solo gli oggetti a cui l'utente deve poter fare accesso, 
		3) revocare l'accesso dell'utente ad un'oggetto in particolare.
	- Il problema delle capability è che non si può affermare di aver rimosso tutte le possibilità di accesso ad un utente se non recidendo l'oggetto stesso.

# 2015/95/28
1. Spiegare almeno tre tipi di controllo che vengono svolti da un fsck su un file system ext2
	- ???

2. Indicare un caso nel quale lo scheduler di tipo Round Robin sia controindicato e spiegarne il motivo.
	- ???

3. A cosa serve l'algoritmo di rimpiazzamento MIN se non puo' essere applicato ai processi in esecuzione?
	- ???

4. Quali sono le differenze nella gestione dei dischi tradizionali e di quelli allo stato solido (SSD) per un sistema operativo? Come differiscono le configurazioni dei due tipi di disco in un sistema Unix (e.g. GNU-Linux).
	- ???

# 2015/02/14
1. Quali sono i casi di frammentazione interna ed esterna che possono avvenire usando la paginazione.
	- ???

2. Per I file system di tipo fat non e' efficiente l'accesso diretto (ad esempio con la system call lseek) a file di grandi dimensioni. Perche'?
	- ???

3. Per quali tipi di processo e' indicato uno schedule a priorita' statica? Quale problema puo' essere causato da uno scheduler a priorita' statica? perche'?
	- ???

4. Cosa e' un knot in un grafo? Quale teorema lega la definizione di knot in un grafo e la presenza di deadlock fra processi?
	- ???


# 2015/01/20
1. Se un sistema ha una RAM molto ampia puo' non essere utile usare la memoria virtuale. In questo caso ha senso egualmente usare la paginazione di memoria? Perche'?
	- ???
2. Perche' i metodi di sincronizzazione tipo test&set (detti anche spinlock) assumono grande rilevanza nella scrittura di sistemi operativi multiprocessore?
	- ???

3. Confrontare gli alogritmi di scheduling roud robin e a priorita' statica. Indicare in quali casi sono da usare algoritmi di tipo round robin e quando quelli a priorita' statica.
	- ???

