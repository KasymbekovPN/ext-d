# ext-d

Утилита для внешнего документирования кода.

## Установка.

Поместить скомпилированый исполняемый файл в рабочую директорию.

## Конфигурационный файл.

Данный файл должен иметь имя *config.json*; *config.json* должен располагаться в рабочей директории.

*config.json* должен содержать массив *targets*, который содержит объекты, включающие в себя пару строк:

* *name* - имя цели,
* *path* - путь до файла описания цели.

Например:

    {
        "targets" : [ 
            {
                "name" : "target-name-1",
                "path" : "path-to-target-description-file-1"
            },
            {
                "name" : "target-name-2",
                "path" : "path-to-target-description-file-2"
            }
        ]
    }

## Файл описания цели.
Json-объект, находящийся в даннм файле, содержит:

* *source-dir* - путь до директории с исходными файлами,
* *out-dir* - путь до выходной директории,
* *lang* - язык,
* *unhandled,files,names* - массив путей до необрабатываемых файлов,
* *unhandled,directory,names* - массив путей до необрабатываемых директорий,
* *tokens,path* - путь до директории с токенами кода (относительно выходного каталога),
* *users,path* - путь до директории с пользовательскими файлами (относитель выходного каталога).

Например:

    {
        "source-dir" : "path-to-source",
        "out-dir" : "path-to-output-directory",
        "lang" : "lang-name",
        "unhandled" : {
            "files" : {
                "names" : [
                    "path-to-unhandled-file-1",
                    "path-to-unhandled-file-2",
                    ....
                    "path-to-unhandled-file-N",
                ]
            },
            "directory" : {
                "names" : [
                    "path-to-unhandled-directory-1",
                    "path-to-unhandled-directory-2",
                    ...
                    "path-to-unhandled-directory-N",
                ]
            }
        },
        "tokens" : {
            "path" : "/relative/path/to/tokens/directory"
        },
        "user" : {
            "path" : "/relative/path/to/users/directory"
        }
    }

## Список поддерживаемых языков:
* *c-lang* 

## Команды:
* --help - вызов справки.
* --version - версия.
* --target.show.all - показать все цели.
* --target.show **target-name** - показать цель **target-name**.
* --target.run **target-name** **flag** - выполнить цель **target-name**
    * **flag** = -d - получить токены кода.
    * **flag** = -m - проверить пользовательские файлы.