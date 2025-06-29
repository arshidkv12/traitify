<?php

/**
 * @generate-class-entries
 * @undocumentable
 */

namespace Traitify;

/**
 * @generate-class-entries
 */
trait Singleton
{
    /** @var static|null */
    protected static $instance;

    /**
     * Get the singleton instance of the class.
     *
     * @return static
     */
    public static function getInstance(): object {}
}



trait Macroable {
    protected static array $macros = [];

    public static function macro(string $name, callable $callback): void {}
    public function __call(string $name, array $arguments): mixed {}
}
