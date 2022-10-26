# Esercizio c.2 (2022/09/06)

Usando i semafori implementare un servizio che preveda due funzioni:
- `void sumstop(int v)`
- `int sumgo(void)`

La funzione `sumstop` deve mettere il processo chiamante in attesa.

La funzione `sumgo` deve sbloccare tutti i processi messi in attesa con la `sumstop` e restituire la somma algebrica dei valori passati come parametro alla `sumstop` dai processi che sono stati sbloccati (zero se la `sumgo` viene richiamata quando non c'è nessun processo bloccato).

[Pagina della wiki aggiornata](https://so.v2.cs.unibo.it/wiki/index.php/20220906c2)


## Esempio Soluzione Errata 1:

```
semaphore sem(1);
int sum=0;
queue q;

void sumstop(int v):
	if i < 0:
		q.enqueue(v)
		sem.P()
	else
		i--

int sumgo(void):
	for each elem in q:
		int val=q.dequeue()
		sum=sum + val
	return sum
```

Commento sul perchè è sbagliato: Non ho `sem.V()`

## Esempio Soluzione Errata 2:

```
queue values;
semaphore s(0);
int sum=0;

void sumstop(int v):
	s.P()
	values.eqnueue(v)

int sumgo(void):
	while !value.isEmpty():
		s.V()
		mutex.P()
		sum=sum+values.dequeue()
		mutex.v()
	return sum
```

Commento sul perchè è sbagliato: Dentro a `sumstop` devo prima incodare il valore e poi bloccare il processo, inoltre `mutex` non è inizializzato

## Esempio Soluzione Errata 3:

```
shared int sum=0;
semaphore wait(0);
semaphore mutex(1);

void sumstop(int v):
	mutex.P();
	sum = sum + v;
	mutex.V();
	wait.P();

int sumgo(void):
	wait.V();
	somma = sum;
	mutex.P()
	sum = 0
	mutex.V()
	return somma;
```

Commento sul perchè è sbagliato:
- La `sumgo` rilascia solo un processo, non tutti
- `somma = sum` è fuori dalla mutua esclusione, è sbagliato

## Esempio Soluzione Errata 4:

```
queue<int> processlist;
semaphore mutex(1);
semaphore s(0);

void sumstop(int v):
	mutex.P();
	processlist.enqueue(v);
	mutex.V();
	S.P();

int sumgo(void):
	int sum = 0;
	mutex.P();
	while processlist.top() != NULL:
		sum += processlist.dequeue();
		S.V();
	mutex.V()
	retutn sum;
```

Commento sul perchè è sbagliato:
- Non bisogna mettere due `mutex.P()` di fila (possibile errore di scrittura)
- `S.P()` fuori alla `mutex` di sumstop fa sbloccare il processo sbagliato
  - **PER RISOLVERE TODO**
- Nota: la `S.V()`  dentro la mutua esclusione si può fare al contrario della `S.P()`

## Esempio Soluzione Errata 5:

```
int counter = 0;
int sum = 0;
semaphore mutex(1);
semaphore blocked(0);

void sumstop(int v):
	mutex.P();
	sum+=v;
	counter++;
	mutex.V();
	blocked.P();

int sumgo(void):
	mutex.P();
	intret = sum;
	sum = 0;
	for (int i=0; i<counter; i++)
		blocked.V()
	counter = 0;
	mutex.V()
	return intret
```

Commento sul perchè è sbagliato:
- **TODO**

## Esempio Soluzione Errata 6:

```
int sum = 0;
mutex = new semaphore(1);
queue q;

void sumstop(int v):
	mutex.P();
	sum += v;
	sintpid = getpid();
	suspend(pid);
	mutex.V();

int sumgo(void):
	mutex.P();
	while !q.empty():
		resume(q.dequeue())
	int value = sum;
	sum = 0;
	return value;
```

Commento sul perchè è sbagliato:
- `ready` e `suspend` sono funzioni del kernel, non vanno usate in un esercizio generico

## Esempio Soluzione Errata 7:

```
int nP, nV = -1, 0;
int somma = 0
int val[]
semaphore mutex(1);
semaphore s(0);

void sumstop(int v):
	mutex.P()
	val[nP++].add[v]
	s.P()
	np--
	v[0].delete

int sumgo(void):
	mutex.P();
	nV++
	if nP > 0:
		s.V()
		for (int i=0; i<nV; i++)
			somma += val[i]
			nv--
	else
		mutex.V()
	return somma
```

Commento sul perchè è sbagliato:
- Utilizzo array sbagliato, indici del for sbagliato, non funziona niente

## Esempio Soluzione Errata 8:

```
struct blocked {
	semaphore sem(0);
	int value = 0;
};

semaphore mutex(1);
list<blocked> procs = new list<blocked>();

void sumstop(int v):
	mutex.P()
	blocked bl = new blocked();
	bl.value = v
	procs.add(bl)
	bl.sem.P()
	mutex.V()

int sumgo(void):
	mutex.P();
	int count = 0;
	foreach proc in procs:
		count += proc.value
		procs.remove(proc)
		proc.sem.V()
	mutex.V()
	return count;
```

Commento sul perchè è sbagliato:
- C'è `s.P()` nella mutua esclusione, quindi deadlock
- Utilizza una lista di semafori, non obbligatoria
- Tiene tutti i valori invece della sola somma

## 9:

```
semaphore s[] new sem(0)
semaphore s1 new sem(0)
int tot, waiting = 0;

void sumstop(int v):
	waiting++
	s[waiting - 1].P()
	waiting--
	tot = tot + v
	if waiting == 0:
		s1.V()

int sumgo(void):
	if waiting = 0:
		return 0
	for (i = waiting -1; i == 0; i--)
		s[i].V()
	s1.P() // per aspettare che tutti abbiano fatto la somma
	return tot
```

Commento sul perchè è sbagliato:
- Manca la mutua esclusione

10:

```
int nw = 0
int currsum = 0
semaphore mutex(1)
semaphore wait2go(0)

void sumstop(int v):
  mutex.P()
	currsum += v;
	nw++;
	mutex.V()
	wait2go.P()
	if --nw > 0:
		wait2go.V()
	else
		mutex.V()

int sumgo(void):
  mutex.P();
	if mw == 0:
		mutex.V()
		return 0;
	int sum = cursum;
	cursum = 0;
	wait2go.V();
	return sum
```

Commento sul perchè è sbagliato: ...

11:

```
semaphore mutex(1);
semaphore semwait(0);
int sum=0;
int wait=0;

void sumstop(int v):
	mutex.P()
	wait++
	sum += v;
	mutex.V()
	semwait.P()
	mutex.P()
	wait--;
	mutex.V()
	if wait > 0:
		semwait.V()

int sumgo(void):
	if wait == 0:
		return 0
	semwait.V();
	while (wait > 0) {}
	int val = sum
	mutex.P()
	sum = 0;
	mutex.V()
	return val;
```

Commento sul perchè è sbagliato: ...

12:

```
semaphore mutex(0)
volatile int counter = 0

void sumstop(int v):
	counter = counter + v;
	mutex.P()

int sumgo(void):
	int val = counter;
	while (mutex.value != 0)
		mutex.V()
	counter = 0;
	return counter
```

Commento sul perchè è sbagliato: ...

## 14

```
semaphore mutex(1)
int sum = 0;
queue of semaphore q;

void sumstop(int v):
	mutex.P()
	sum += v;
	s = new semaphore(0);
	q.enqueue(s)
	mutex.V()
	s.P()
	free(s)
	if(q.empty())
		mutex.V()
	else
		semaphore s = q.dequeue()
		s.V()

int sumgo(void):
	mutex.P()
	int lsum = sum
	sum = 0
	if(q.empty())
		mutex.V()
	else
		semaphore s = q.dequeue()
		s.V()
```

Corretto, manca solo la restituzione della somma alla fine di `sumgo` (`return lsum`)