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
