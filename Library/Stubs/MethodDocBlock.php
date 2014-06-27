<?php

namespace Zephir\Stubs;

use Zephir\ClassMethod;

class MethodDocBlock extends DocBlock
{
    private $parameters = array();
    private $return;

    public function __construct(ClassMethod $method, $indent = 4)
    {
        parent::__construct($method->getDocBlock(), $indent);
        $this->parseLines();
        $this->parseMethodParameters($method);
        if (!$this->return) {
            $this->parseMethodReturnType($method);
        }
        if ($this->parameters) {
            $this->appendParametersLines();
        }
        if ($this->return) {
            $this->appendReturnLine();
        }
    }

    protected function parseMethodReturnType(ClassMethod $method)
    {
        if (is_array($this->return)) return;

        $return = array();
        $returnTypes = $method->getReturnTypes();
        if ($returnTypes) {
            foreach ($returnTypes as $type) {
                if (isset($type['data-type'])) {
                    $return[] = $type['data-type'];
                }
            }
        }
        $returnClassTypes = $method->getReturnClassTypes();
        if ($returnClassTypes) {
            $return = array_merge($return, $returnClassTypes);
        }
        if ($return) {
            $this->return = array(join('|', $return), '');
        }
    }

    protected function parseLines()
    {
        $lines = array();

        foreach ($this->lines as $line) {
            if (preg_match('#@(param|return) *([\w\\\|]+)* *(\$?\w+)* *(.+?)*#', $line, $matches) === 0) {
                $lines[] = $line;
            } else {

                @list(, $docType, $type, $name, $description) = $matches;

                switch ($docType) {
                    case 'param':
                        $this->parameters[$name] = array($type, $description);
                        break;
                    case 'return':
                        $this->return = array($type, $description);
                        break;
                }
            }
        }
        $this->lines = $lines;
    }

    private function appendReturnLine()
    {
        list($type, $description) = $this->return;
        $this->lines[] = '@return ' . $type . ' ' . $description;
    }

    private function parseMethodParameters(ClassMethod $method)
    {
        if (count($this->parameters)) return;
        $parameters = $method->getParameters();
        if (!$parameters) {
            return;
        }
        foreach ($method->getParameters() as $parameter) {
            if (isset($parameter['data-type'])) {
                if ($parameter['data-type'] == 'variable') {
                    $type = 'mixed';
                } else {
                    $type = $parameter['data-type'];
                }
            } elseif (isset($parameter['cast'])) {
                $type = $parameter['cast']['value'];
            } else {
                $type = 'mixed';
            }
            if (!isset($this->parameters['$' . $parameter['name']]) && !isset($this->parameters[$parameter['name']])) $this->parameters['$' . $parameter['name']] = array($type, '');
        }
    }

    private function appendParametersLines()
    {
        foreach ($this->parameters as $name => $parameter) {
            list($type, $description) = $parameter;
            if (strlen($name) && strpos($name,"$") !== 0) $name = '$'.$name;
            $this->lines[] = '@param ' . $type . ' ' . $name . ' ' . $description;
        }
    }
}
