--TEST--
Traitify\Macroable: basic macro registration and call
--EXTENSIONS--
traitify
--FILE--
<?php

use Traitify\Macroable;

class Tool {
    use Macroable;
}

Tool::macro('greet', fn($name) => "Hello, $name!");
$t = new Tool();
echo $t->greet("Arshid"), "\n";

// test multiple macros
Tool::macro('add', fn($a, $b) => $a + $b);
echo $t->add(2, 3), "\n";

// test missing macro
try {
    $t->missing();
} catch (Throwable $e) {
    echo "Caught: " . $e->getMessage() . "\n";
}

?>
--EXPECT--
Hello, Arshid!
5
Caught: Macro 'missing' not found
