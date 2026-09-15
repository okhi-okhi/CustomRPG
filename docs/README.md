# Overview

&#x20;[**Documentation**](https://customrpg.gitbook.io/docs/)

### What is CustomRPG?

CustomRPG is a turn-based RPG game engine that allows anyone to create a complete RPG game with just JSON files. No programming skills are required.

### Features

* **Easy to use:** CustomRPG is designed to be easy to use, even for beginners. Just create JSON files and run the engine.
* **Highly customizable:** CustomRPG allows you to change almost anything in the game except layout and gameplay.
* **Free and open source:** CustomRPG is free and open source, so you can use it for any purpose.

### **Example** setting **file**

For example, the following enemy setting file defines a goblin axeman:

{% code title="entitys\enemys\goblin_axe.json" fullWidth="false" %}
```json
{
    "name": null,
    "level": {"min": 1, "max": 20},
    "hpMax": "20+level*0.5",
    "manaMax": "10+level*0.5",
    "atk": "10+level*0.3",
    "defense": 5,
    "dropExp": "20+level*4",
    "dropGold": "5+level",
    "talent": {
        "strength": "level",
        "stamina": "level*1.5",
        "dexterity": "level*0.5",
        "intelligence": 1
    },
    "attackTypes":{
        "normal": 0.9,
        "skill": 0.1
    },
    "skills":{
        "roar": 1
    },
    "dropItems":{
        "weapon":{
            "broken_axe": 0.05
        },
        "armor":{
            "broken_head": 0.01,
            "broken_boots": 0.02
        }
    }
}
```
{% endcode %}

The strength of enemies can be scaled with level, so you don't have to create multiple files for different levels of the same enemy.&#x20;

This is just one example of how CustomRPG's settings files are designed to reduce the burden on creators while still allowing for a high degree of customization.
