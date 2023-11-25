# Régulation d'alimentation

## Objectif final

L'objectif est la conception d'une alimentation DC/DC avec un MPPT pour un panneau de 14 cellules SunPower C60 montées en série.

L'accumulation d'énergie se fait sur une banque de condensateurs d'environ 10F pour une tension admissible de 20V.

| Grandeur  | Cellule | Panneau |
| --------- | ------- | ------- |
| $V_{MPP}$ | 0.574   | 8.036   |
| $I_{MPP}$ | 5.83    | 5.83    |
| $P_{MPP}$ | 3.34    | 46.85   |

## Proposition

Afin de réaliser cette fonction, je propose l'utilisation d'un régulateur boost synchrone (Référence TPS61178, `U1`). La tension de sortie de ce module est ajustable via un pont diviseur (`R5`  et `R3` ) dont la tension du point milieu $V_{FB}$ sera ajustée à 1.2V . Le courant consommé par le pin `FB` (`U1:5`) est négligeable  (moins de 60nA). 



Pour ajuster (élever) la tension de sortie $V_{OUT}$ par rapport à la tension par défaut du pont diviseur proposé (8.4V), je propose l'utilisation d'un transistor bipolaire `Q1` pour "consommer" (_sink_) 1mA sur le point milieu ce qui, avec une résistance côté haut de 12k, correspond à une élévation de 12V de $V_{OUT}$ .

En admettant une tension $V_{ADJ}$ maximale de 1.66V pour 1mA consommé et en considérant la tension $V_{BE}$ = 0.66 V du transistor `Q1` , on a en principe :

$$
I_C = \beta \times I_B
$$

$$
I_C = \beta \times \frac{ V_{ADJ} - V_{BE} }{R_4}
$$

$$
R_4 = \beta \times \frac{1.66-0.66}{I_C}
$$

$$
R_4=\beta \times 1000
$$

Donc, pour $\beta \in [200;400]$ on a $R_4 \in [200e3;400e3]$ avec un courant $I_B$ maximal inferieur à 2.5$\mu$A

D'un point de vue fréquence de mise à jour de la consigne, on peut supposer une fréquence lente vis à vis des fréquences de fonctionnement du régulateur. Par exemple, maximum, 1kHz (à comparer aux 200kHz-2MHz du switching).

## Problèmes potentiels

- Est-ce que cette architecture est pertinente ?

- Est-il possible/pertinent d'utiliser un BJT pour cette application, notemment lorsque des courants aussi faibles sont en jeu ? 

- Quelles seraient les précautions à prendre, notamment sur les paramètres du BJT et/ou de l'AOP ?


