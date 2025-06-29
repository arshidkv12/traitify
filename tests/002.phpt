--TEST--
Traitify\Singleton basic singleton behavior
--EXTENSIONS--
traitify
--FILE--
<?php

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

var_dump($a === $b);
echo $a->hello(), "\n";

?>
--EXPECT--
Constructing...
bool(true)
Hello World
