# Esecizio 1
## Dato un message passing asincrono FIFO `asend/arecv` vogliamo un servizio message passing asincrono LIFO `lasend/larecv`

```
int n_processes;
stack last[n_processes]; //uno stack per ogni mittente
lasend(msg_t msg, pid q):
  p = getpid();
  asend(<msg, p>, q);

//senza la gestione ANY!
lareceive(pid q):
  p = getpid();
  asend(<'MYMESSAGE', p>, p); //automessaggio
  //adesso dobbiamo fare un loop per ricevere tutti i messaggi
  while (true)
      <msg, mittente> = areceive(ANY);
      if( msg == 'MYMESSAGE' && mittente == p)
           break;
      last[mittente].push(msg);

  //adesso lo stack contiene tutti i messaggi ricevuti
  while(last[q].isEmpty())
    <msg, mittente> = areceive(ANY);
    last[mittente].push(msg)
  return last[q].pop();

//mettiamo una struttura dati che gestisca lei la richiesta any e 'il gioco è fatto'


//aggiungiamo la gestione ANY!

int n_processes;
multistack mlast
lasend(msg_t msg, pid q):
  p = getpid();
  asend(<msg, p>, q);

lareceive(pid q):
  p = getpid();
  asend(<'MYMESSAGE', p>, p); //automessaggio
  //adesso dobbiamo fare un loop per ricevere tutti i messaggi
  while (true)
      <msg, mittente> = areceive(ANY);
      if( msg == 'MYMESSAGE' && mittente == p)
           break;
      mlast.add(msg,mittente);

  //adesso lo stack contiene tutti i messaggi ricevuti
  while((msg = mlast.get(q)) == NULL)
    <msg, mittente> = areceive(ANY);
    mlast.add(msg,mittente);
  return msg
```