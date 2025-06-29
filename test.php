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