# FIWARE Context Broker development environmet

This is a Development enviroment for Orion. It install for you an environment with all the dependencies and libraries compiled and installed ready to develop new feature for Orion.
This project contains as a git submodule the fiware-orion folder, which is shared inside the container on the path `opt/fiware-orion`

## Seting up the enviroment

Before start developing new features for Orion Context Broker, you need to setup the enviroment. This means create an image with all the libraries installed

For building the enviroment, you have to run

`docker build -t orion .`

This will create a container from base image and install dependencies (it can take more than 15 minutes). 

Once you have build the image, you can bringing up the enviroment:

`docker-compose up -d`

### Updating Dockerfile

In case of Orion updates the libraries or dependencies, you will have to modify the dockerfile wiht new changes.

For this purpose, the Dockerfile in this repo is a subset of the one in Orion repo. You have to copy all the dockerfile until starts Orion compilation
(typically until line `# Install orion from source`). Do not forget to remove `&& \`at the end of the last line, otherwise you would get a syntaxt error while
building the docker image.

### How to create an image a publish it to Docker hub

In the case you can create a docker image on Docker hub to save time next time you want to use that image, you have to follow this process:

Create tag

First, image id `docker image list` and dockerhub destination
``` 
docker tag 35d8c9e2eb42 mapedraza/dev-orion:latest
docker push mapedraza/dev-orion:latest
```

## Start developing

### Editing the code

The source code folder available on the folder project, `fiware-orion` contais Orion Context Broker code. You can update it or modify it usinsg your favorite IDE or editor

### Compiling

First, you need to connect to docker container enviroment to be able to compile the system

`docker-compose exec orion /bin/sh`

Then, you can connect inside the machine (`docker-compose exec orion /bin/sh`) and build with the following command:

``` bash
cd /opt/fiware-orion && \
make && \
make install
```

### Running

For runing Orion, you can use the following command

`/opt/fiware-orion/BUILD_RELEASE/src/app/contextBroker/contextBroker -fg -multiservice -ngsiv1Autocast -disableFileLog -logLevel DEBUG -noCache -dbhost mongo`


/opt/fiware-orion/BUILD_RELEASE/src/app/contextBroker/contextBroker -fg -multiservice -ngsiv1Autocast -disableFileLog -logLevel DEBUG -noCache -dbhost mongo -logSummary 15 | tee >(sed -n '/SUMMARY/p' >healthcheck)

If fails when trying to run it wiht the following message `msg=PID-file '/tmp/contextBroker.pid' found. A broker seems to be running alreadyV`

Use this command

```
rm /tmp/contextBroker.pid
```

# Submodules

Son repos dentro de otro repo

Example how to create a new folder with a submodule

```bash
git submodule add git@github.com:mapedraza/fiware-orion.git
```

If you want to move the submodule to a particular tag:

```bash
cd submodule_directory
git checkout v1.0
cd ..
git add submodule_directory
git commit -m "moved submodule to v1.0"
git push
```

Then, another developer who wants to have submodule_directory changed to that tag, does this

```bash
git pull
git submodule update --init
git pull changes which commit their submodule directory points to. git submodule update actually merges in the new code.
```



For creating a new branch inside submodule
```
cd submodule_directory
git checkout -b task/new_feature
git push -u origin task/new_feature
cd ..
git add submodule_directory
git commit -m "created branch task/new_feature"
git push
```



To forze synchronize submodule forked with upstream (fork father) (will copy exactly upstream to the fork deleting all changes)

```
git remote add upstream https://github.com/some_user/some_repo
git fetch upstream
git checkout master
git reset --hard upstream/master  
git push origin master --force
```