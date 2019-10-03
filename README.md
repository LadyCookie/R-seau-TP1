#Quel protocole transport utilisez-vous pour ce genre de message?
Nous utilisons TCP car les QoS requises pour un tel service nécessite une fiabilité dans l'envoi et la réception des données.
Par exemple, un chat où il est possible d'écrire un message et que seule 50% des personnes ciblées le recoive serait nul.
D'autre part, l'utilisation de la bande passante pour communiquer des messages textuels n'est pas très importante, donc cela n'a pas beaucoup d'impact.