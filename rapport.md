% Système d'exploitation -- TP3
% Vincent Antaki et Guillaume Poirier-Morency

Pour compiler, un `Makefile` est fournit, alors il suffit de lancer la
commande:

```bash
make
```



1. Stratégie de remplacement pour le TLB

Pour la TLB, nous avons utilisé LFU comme algorithme de remplacement car, des trois algorithmes implantés, c'est celui qui se comportant le mieux avec l'exemple "addresse.txt".

Chaque algorithme de remplacement à ses cas où il

LFU fonctionne bien lorsqu'un nombre limité de frames ont un nombre d'accès beaucoup plus élevé que les autres et que ceux-ci sont appelés...

LRU fonctionne bien lorsque les accès à une frame particulière sont  rapprochés.

FIFO fonctionne bien lorsque les accès à une frame particulière sont très rapprochée, voir quasi-consécutive. 


2.
Le Page Fault Ratio est le même indépendamment de l'algorithme de TLB utilisé. Si le nombre de page à charger est inférieur au nombre de place en mémoire physique, le page fault ratio sera toujours "le nombre de page à charger"/"le nombre total de requete". 


Pour "adresse.txt", il est de 18/1000 car seul 18 page sont utilisé dans l'exemple

Pour changer l'algorithme de remplacement, il changer la ligne "#define LFU" dans le fichier "common.h" par "#define FIFO" ou par "#define LRU". Il est important de n'avoir qu'un seul de ces define de présent sinon on se retrouve avec plus qu'une fonction addentry pour le TLB.

LFU est de l

LRU nous donne 0.59???

FIFO nous donn 0.56

3.

