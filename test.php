<?php 

class MyService {
    use Traitify\Singleton;

    function hello(){
        return "hello";
    }

    private function __construct()
    {
        echo 9;
    }

}

$a = MyService::getInstance();
$b = MyService::getInstance();

var_dump($a === $b); // true

var_dump( $a->hello() );