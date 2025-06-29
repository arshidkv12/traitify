<?php 

 


use Traitify\Macroable;

class Tool {
    use Macroable;
}

Tool::macro('greet', fn($name, $age) => "Hello, $name! $age");
Tool::macro('greet1', fn($name) => "Hello---, $name!");
$t = new Tool();
echo $t->greet1("Arshid");
echo $t->greet("Arshid", 33);