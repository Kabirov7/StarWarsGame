# SDL2 GAME STAR WARS 1.0

- Использование SDL2 в качестве инструмента обработки графики и звука
- Использование GoF паттернов проектирование
- Использование библиотеки XMLparsing. [Original code by Lee Thomason](www.grinninglizard.com)
- Использование декодировки Base64 zlib compression (Copyright (C) 2004-2008 René Nyffenegger)


**Идея:**
На планету напали и хотят её захватить. Наша задача защитить нашу планету и каждый раз сражаться с Боссами
<img width="752" alt="Boss" src="https://user-images.githubusercontent.com/58626168/173397459-04c2ca3b-7bce-4b0d-93f0-a50af14916fd.png">
<img width="752" alt="Game" src="https://user-images.githubusercontent.com/58626168/173397513-235e944e-823f-484f-8144-3e5e293c7a26.png">


## Установка игры
1. Установить библиотеку SDL2, SDL2_image, SDL_mixer
2. Добавить корневую диррикторию в конфигурации запуска (В Clion `Edit configurations > Working dirictory` и добавить `$ProjectFileDir$`)
3. Собрать проект `cd build`
4. Запустить проект
> #### Установку приложения Tiled можно посмотреть здесь https://www.mapeditor.org/

## Главные состояния игры
Все страницы игры парсятся из файла `assets/attack.xml`. 
Данная структура хранения позволяет легко создавать объекты на страницах жестко не прописывая их.
```
<MENU>
        <TEXTURES>
            <texture filename="assets/clouds2.png" ID="background"/>
            <texture filename="assets/button.png" ID="playbutton"/>
            <texture filename="assets/exit.png" ID="exitbutton"/>
        </TEXTURES>

        <OBJECTS>
            <object type="AnimatedGraphic" textureID="background" numFrames="1" animSpeed="1"/>
            <object type="MenuButton" x="100" y="100" width="400" height="100" textureID="playbutton" numFrames="0" callbackID="1"/>
            <object type="MenuButton" x="100" y="300" width="400" height="100" textureID="exitbutton" numFrames="0" callbackID="2"/>
        </OBJECTS>
</MENU>
```
<img width="752" alt="Main Menu State" src="https://user-images.githubusercontent.com/58626168/173397600-91443cea-ba3f-498c-b975-4d8db4b248ed.png">
<img width="752" alt="Pause State" src="https://user-images.githubusercontent.com/58626168/173397624-f4d00f4d-7e8f-4720-93dc-d3dd934d5499.png">
<img width="752" alt="Game Over State" src="https://user-images.githubusercontent.com/58626168/173397646-4f25b48d-09d7-4d3a-b2a4-acd1a5af35af.png">


## Игра
В игре нет лучших результатов, зато есть уровни, которые игрок может пройти. 
Для каждого уровня пердусмотрен конкретный файл в котором уже определены положения врагов, стен и всей остальной информации.
Для более меньшего объема занимаемой памяти уровнем я использовай tile, которые создавал в бесплатном приложении Tiled, где и сжимал информацию для уровня с помощью Base64 zlib compression.
Для грамотного парсинга карты tile я использовал Base64 zlib decoder. Это позволило мне сэкономить памяти на компьютере.
Так же Tiled позволяет добавлять информацию для карты и для объектов которые на ней находятся. В каждой карте я предусмотрел 5 слоев.
<img width="752" alt="Game" src="https://user-images.githubusercontent.com/58626168/173397513-235e944e-823f-484f-8144-3e5e293c7a26.png">
<img width="752" alt="Boss" src="https://user-images.githubusercontent.com/58626168/173397459-04c2ca3b-7bce-4b0d-93f0-a50af14916fd.png">

## Смерть и возраждение
У игрока всегда на начало игры предусмотрено 3 жизни. 
После смерти игрок некоторое время не уязвим, это помогает понять возможность регулировки
alpha каналов текстуры в изображении, пока игрок "мигает" он неуязвим

## Босс
Для каждого уровня предусмотрен босс в конце уровня. После одержания победы игрок улетает за экран
и попадает на следующий уровень.

## Создание нового уровня в приложении Tiled
Создание нового уровня предусматривает использование приложения tiled для создания карты для двумерных игр.
В предыдущих абзацах я рассказал какие слои обязательно должен содержать любой уровень
<img width="1795" alt="Tiled App" src="https://user-images.githubusercontent.com/58626168/173398447-3752788a-10e5-4e13-8f95-48818c0b2216.png">

1. Object Layer 2 (он же background) в нем хранится изображение для фона игры
2. Collision Layer. На этом слое я рисовал карту и если игрок врезался в него то он умирал.
3. Object Layer 1. На этом слоя я разместил все объекты игры которые изначально должны появится прям на карте. Объекты такие как: вражеские самолеты, они же глайдеры, туррели и т.д.
4. Tile Layer. Из-за того что туррели должны находиться за tile'ом горки. я наложил на него ещё одну текстуру.
5. Object Layer 3. Для расположения объектов которые создаются вне карты, такие как эсколэйторы.
<img width="545" alt="Player object properties" src="https://user-images.githubusercontent.com/58626168/173398517-6ffe6fe3-82b5-4639-98f8-6bbe0fda811c.png">
<img width="519" alt="Map Layers" src="https://user-images.githubusercontent.com/58626168/173398463-04e788e1-8952-487c-9020-0e298eb0d068.png">
<img width="343" alt="Map Properties" src="https://user-images.githubusercontent.com/58626168/173398543-990d2e92-0c74-4c0f-b506-92a4d4437264.png">
<img width="545" alt="Player object properties" src="https://user-images.githubusercontent.com/58626168/173398668-d65b4245-ec68-4ab7-9e08-b2d6c3edc03c.png">


## Основные элементы игры
В моей игре я использовал одни из Gof'ерских паттернов проектирования, такие как: фабрика объектов, машина состояний, single'тоны, хранители и многое другое.
Одни из главных файлов находятся в директории `GameFramework/`.
Так же я пытался организовать правильную иерархию классов и у меня получилось это сделать.

<img width="255" alt="GameFramework Folder" src="https://user-images.githubusercontent.com/58626168/173399050-8bd11313-f2e6-4bda-a6f1-2421a40b243b.png">


## Почему всё работает именно так?
- Я не хотел жестко хардкодить объекты на экране и решил что парвильно было бы читать их из файла, как это делают, например, разработчики android приложений.
Из-за этого я решил использовать xml файлы в качестве разметки основных элементов состояния. 
- Я решил что хочу игру похожую на "Mario"
- Я пытался создать проект чтобы в дальнейшем его код можно было переиспользовать. 
И кажется, у меня получилось это сделать. 
Сейчас чтобы изменить мою игру достаточно поменять логику элементов в папке `GameObjects/`.
Если вы хотите сделать Mario 2.0 version, то просто поменяйте изображения в папке `assets/`.
Перепишите логику врагов и запретите самолету летать 🤗

## Что можно улучшить?
1. Добавить выбор уровня или ведение учетной записи игрока, чтобы игра стала похоже больше на приключенческую.
2. добавить больше атрибутов и информации в объекты на экране а не прописывать их в самой программе.
3. Автоматизировать создание карты чтобы все объкты создавались динамически, но я думаю вряд-ли это можно сделать "красиво" без использования ИИ


## Прохождение первого уровня 

https://user-images.githubusercontent.com/58626168/173402813-db06beaf-6160-42f2-8980-43a5c56b7ed3.mp4

