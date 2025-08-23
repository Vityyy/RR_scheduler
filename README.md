**README** available in English and Spanish | **README** disponible en Inglés y en Español

# sched — Scheduler Project

Repository for the solution of the [TP sched](https://fisop.github.io/website/tps/sched) from the **Mendez-Fresia** course of **Operating Systems (7508) - FIUBA**.


## Theoretical answers

Use the `sched.md` file provided in the repository.

## Compile

By _default_, the _scheduler_ will be compiled in **round-robin** mode:

```bash
make
```

## Conditional compilation of _schedulers_

To compile and test the kernel with both schedulers:

- **round-robin**:

```bash
make <target> USE_RR=1
```

- **priorities**:

```bash
make <target> USE_PR=1
```

## Tests

```bash
make grade
```

## Docker

A `dock` _script_ is provided to run the following commands:
- **build**: builds the project image using the provided `Dockerfile`.
- **run**: creates a _container_ from the image and runs it.
- **exec**: opens a new _shell_ inside the existing _container_.

Inside the _container_, all commands from the `GNUmakefile` can be executed, such as `make grade` or `make qemu-nox`.

The _container_ uses [mount volumes](https://docs.docker.com/storage/volumes/), so changes made outside the container will automatically be visible inside.

## Linter

```bash
$ make format
```

To commit the formatting changes:

```bash
$ git add .
$ git commit -m "format: apply code formatter"
```



------------------------------------------------------------------------------------



# sched - Proyecto Scheduler

Repositorio para la solución del [TP sched](https://fisop.github.io/website/tps/sched) del curso Mendez-Fresia de **Sistemas Operativos (7508) - FIUBA**

## Respuestas teóricas

Utilizar el archivo `sched.md` provisto en el repositorio

## Compilar

Por _default_ se compilará el _scheduler_ en versión **round-robin**.

```bash
make
```

## Compilación condicional de _schedulers_

Para compilar y probar el kernel y poder probar ambos planificadores, se puede:

- **round-robin**:

```bash
make <target> USE_RR=1
```

- **priorities**:

```bash
make <target> USE_PR=1
```

## Pruebas

```bash
make grade
```

## Docker

Se provee un _script_ `dock` que permite ejecutar los siguientes comandos:

- **build**: genera la imagen del proyecto usando el `Dockerfile` provisto
- **run**: genera un _container_ a partir de la imagen anterior y lo corre
- **exec**: permite abrir una nueva _shell_ en el _container_ anterior

Dentro del _container_ se pueden ejecutar todos los comandos provistos por el `GNUmakefile` como `make grade` o `make qemu-nox`.

El _container_ utiliza [mount volumes](https://docs.docker.com/storage/volumes/) con lo cual los cambios que se realicen por fuera del mismo, serán visibles de forma automática.

## Linter

```bash
$ make format
```

Para efectivamente subir los cambios producidos por el `format`, hay que `git add .` y `git commit`.
