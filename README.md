Pasos:

Crear el repositorio

git clone https://github.com/LeDaVR/Proyecto.git

Para crear un branch 

git branch Leonardo-Valdivia
git checkout Leonardo-Valdivia

git status 


```
[leonardo@leonardo-nitroan51553 Proyecto]$ git status
En la rama Leonardo-Valdivia
Archivos sin seguimiento:
  (usa "git add <archivo>..." para incluirlo a lo que se será confirmado)
        glad.c
        include/
        main.cpp
        models.txt
        movementSystem/
        resources/
        shaders/

no hay nada agregado al commit pero hay archivos sin seguimiento presentes (usa "git add" para hacerles seguimiento)
```

realizar los cambios 

git add .
git commit -m proyecto
git push origin Leonardo-Valdivia

```
[leonardo@leonardo-nitroan51553 Proyecto]$ git push origin Leonardo-Valdivia
Username for 'https://github.com': ledavr 
Password for 'https://ledavr@github.com': 
Enumerando objetos: 70, listo.
Contando objetos: 100% (70/70), listo.
Compresión delta usando hasta 8 hilos
Comprimiendo objetos: 100% (67/67), listo.
Escribiendo objetos: 100% (69/69), 8.22 MiB | 816.00 KiB/s, listo.
Total 69 (delta 13), reusado 0 (delta 0), pack-reusado 0
remote: Resolving deltas: 100% (13/13), done.
remote: 
remote: Create a pull request for 'Leonardo-Valdivia' on GitHub by visiting:
remote:      https://github.com/LeDaVR/Proyecto/pull/new/Leonardo-Valdivia
remote: 
To https://github.com/LeDaVR/Proyecto.git
 * [new branch]      Leonardo-Valdivia -> Leonardo-Valdivia

```
Hacer merges

git checkout master
git merge Leonardo-Valdivia

git log

```
[leonardo@leonardo-nitroan51553 Proyecto]$ git log
commit e13d38d59a9bd024702cf9be112efd7d882cd8a6 (HEAD -> master, origin/Leonardo-Valdivia, Leonardo-Valdivia)
Author: ledavr <danielvaldiviaramos@hotmail.com>
Date:   Wed Sep 23 10:02:28 2020 -0500

    proyecto

commit dbe6e24fd77190330ba49e26aae9845e09dd8f38 (origin/master)
Author: ledavr <danielvaldiviaramos@hotmail.com>
Date:   Wed Sep 23 09:58:34 2020 -0500

    readme
```
