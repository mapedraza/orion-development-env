# FIWARE Context Broker development environmet

This is a Development enviroment for Orion

For building the enviroment

`docker build -t orion .`

This will create the image (it can take more than 15 minutes)


For bringing up the enviroment:

`docker-compose up -d`



## How to create an image a publish it to Docker hub

Create tag

First, image id `docker image list` and dockerhub destination
``` 
docker tag 35d8c9e2eb42 mapedraza/dev-orion:latest
docker push mapedraza/dev-orion:latest
```


## How to connect inside docker container

`docker-compose exec orion /bin/sh`

## How to modify the code

The source code folder available on the folder fiware-orion contais the Broker code. You can update it or modify it. 

Then, you can connect inside the machine (`docker-compose exec orion /bin/sh`) and build with the following command:

``` bash
cd /opt/fiware-orion && \
make && \
make install
```

And run it with:

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



For creating a new branch
```
cd submodule_directory
git checkout -b task/new_feature
cd ..
git add submodule_directory
git commit -m "created branch task/new_feature"
git push
```