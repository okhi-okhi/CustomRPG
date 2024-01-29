---
description: All items can be stored in the player's unlimited inventory.
---

# Item

### **Item**

There are four types of items in the game:

* [**Weapon**](item.md#weapon)
* [**Armor**](item.md#armor)
* [**Material**](item.md#material)
* [**Prop**](item.md#prop)

### **Item Properties**

All items have the following properties:

* **Name**
* **Buy Price**
* **Sell Price**
* **Rarity**

{% hint style="warning" %}
The rarity of the item. Rarer items are more difficult to obtain.The rarity categories are defined in the game config.**(This feature has not been implemented yet)**
{% endhint %}

### **Weapon**

* [**Weapon Type**](item.md#weapon-type)
* **Level**
* **Attack**
* **Defense**
* **Critical Chance**
* **Critical Damage**
* **Durability**
* **Durability Max**

{% hint style="info" %}
When the durability of an item returns to zero, the item will be damaged and disappear. Materials can be used to repair the item.
{% endhint %}

### Armor

* [**Armor Type**](item.md#armor-type)
* **Level**
* **Attack**
* **Defense**
* **Durability**
* **Durability Max**

### **Material**

* **Description**
* **some recipe stuff (TODO)**

### **Prop**

* **Description**
* **some onUse effect (TODO)**

### **Weapon Type**

Affect the some properties for weapons.

* **Description**
* **Combo Rate:** The chance of continuous normal attacks.
* **Hands**
* **Hidden:** Whether it is hidden in the forging menu and can only be forged using special formulas.
* **Passives**

### **Armor Type**

Affect the some properties for armors.

* **Description**
* **Armor Slot**
* **Hidden:** Whether it is hidden in the forging menu and can only be forged using special formulas.
* **Passives**
