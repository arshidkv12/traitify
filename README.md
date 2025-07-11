# Traitify PHP Extension

**Traitify** is a native PHP extension that provides commonly used traits such as `Singleton`, implemented in C for optimal performance and better memory efficiency.

---

## 🧩 Features

- ✅ Native `Traitify\Singleton` trait
- ✅ Automatic singleton management (`getInstance()`)
- ✅ Proper support for `__construct()`
- 🚀 Built for speed — skips PHP overhead
- 🧠 Extendable for more traits like `Macroable`, `Loggable`, etc.

---

## 📦 Installation

### 1. Clone and build

```bash
git clone https://github.com/yourname/traitify.git
cd traitify

phpize
./configure --enable-traitify
make
sudo make install
```


### 2. Enable in php.ini
```bash
extension=traitify.so
```

### ✨ Example Usage
 
#### Singleton Trait

```php
<?php
use Traitify\Singleton;

class MyService {
    use Traitify\Singleton;

    public function __construct() {
        echo "Constructing...\n";
    }

    public function hello() {
        return "Hello World";
    }
}

$a = MyService::getInstance();
$b = MyService::getInstance();

var_dump($a === $b);   // true
echo $a->hello();      // Hello World
```


#### Macroable Trait

```php
<?php

use Traitify\Macroable;

class Tool {
    use Macroable;
}

Tool::macro('greet', fn($name) => "Hello, $name!");
$t = new Tool();
echo $t->greet("Arshid"); // Hello, Arshid


