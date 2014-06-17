<?php

$aliases['valencia'] = array(

    'databases' => array(
        'default' => array(
            'default' => array(
                'driver' => 'mysql',
                'username' => 'root',
                'password' => 'root',
            ),
        ),
    ),
    'command-specific' => array(
        'site-install' => array(
            'account-name' => 'john.smith',
            'account-pass' => 'lifeislifelalalalala',
            'account-mail' => 'bdoesborg@gmail.com',
            'site-mail' => 'bdoesborg@gmail.com',
            'yes' => FALSE,
        ),
    ),
);


$aliases['cnectmess'] = array(
    'parent' => '@valencia',
     'root' => '/Users/boris/Sites/DAE/trunk',

);

$aliases['nee.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'neelie.val',
    'path-aliases' => array(
        '%files' => 'sites/neelie_kroes/files',
    ),
);

$aliases['cne.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'cnect.val',
    'path-aliases' => array(
        '%files' => 'sites/cnect/files',
    ),
);

$aliases['h20.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'h2020.val',
    'path-aliases' => array(
        '%files' => 'sites/h20/files',
    ),
);

$aliases['dae.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'dae.val',
    'path-aliases' => array(
        '%files' => 'sites/dae/files',
    ),
);

$aliases['dch.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'dae-cheat.val',
    'path-aliases' => array(
        '%files' => 'sites/dae-cheat/files',
    ),
);

$aliases['dae2.val'] = array(
    'parent' => '@valencia',
    'root' => '/Users/boris/Sites/dae2/docroot',
    'uri' => 'dae2.val',
    'path-aliases' => array(
        '%files' => 'sites/dae2/files',
    ),
);

$aliases['l4e.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'l4e.val',
    'path-aliases' => array(
        '%files' => 'sites/l4e/files',
    ),
);

$aliases['ssk.val'] = array(
    'parent' => '@cnectmess',
    'uri' => 'ssk.val',
    'path-aliases' => array(
        '%files' => 'sites/site_starter_kit/files',
    ),
);
