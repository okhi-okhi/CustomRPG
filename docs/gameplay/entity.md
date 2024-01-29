---
description: An entity is any living being in the game world that can engage in combat.
---

# Entity

### **Entity**

There are two types of items in the game:

* [Ally](entity.md#ally)
* [Enemy](entity.md#enemy)

### **Entity P**roperties

All entities have the following properties:

* **Name**
* **Level**
* **HP**
* **Max HP**
* **Mana**
* **Max Mana**
* **Attack**
* **Defense**
* **Talents**

{% hint style="info" %}
Talents are special abilities that can provide the entity with various bonuses. The specific kinds of talents can be changed in the game's configuration.
{% endhint %}

### Ally

Allies are player-controlled entities.

* **Experience**
* **Luck:** Affects the drop rate of items, which can affect combat.
* **Talent Point:** Can be consumed to upgrade any talent.
* **Race:** Affects the ally's initial stats and can have passive abilities.
* **Occupation:** Affects the stats that the ally gains each level and can have skills.
* [**Equipment**](equipment.md)

{% hint style="info" %}
#### Level up

When an ally reaches a certain amount of experience, it will level up. When an ally levels up, its stats will increase according to its occupation and it also gains 1 talent point.
{% endhint %}

### Enemy

Enemies are non-player-controlled hostile entities that cannot wear equipment.

* **Drop Exp:** Experience points dropped when killed. Will be evenly distributed to allies in the player's combat team.
* **Drop Gold:** Gold dropped when killed.
* **Attack Types:** The probability of using normal attacks or skills.
* **Skills:** Skills that can be used, and the conditions for casting.
* **Drop Weapons:** The probability of dropping specific weapons.
* **Drop Armors:** The probability of dropping specific armor.
