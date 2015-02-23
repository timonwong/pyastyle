Python module for astyle
========================

| |version| |travis| |appveyor|

.. |version| image:: https://pypip.in/version/pyastyle/badge.svg?style=flat
    :alt: PyPI Package latest release
    :target: https://pypi.python.org/pypi/pyastyle

.. |travis| image:: https://travis-ci.org/timonwong/pyastyle.svg?branch=master
    :alt: Travis-CI Build Status
    :target: https://travis-ci.org/timonwong/pyastyle

.. |appveyor| image:: https://ci.appveyor.com/api/projects/status/github/timonwong/pyastyle?branch=master&svg=true
    :alt: AppVeyor Build Status
    :target: https://ci.appveyor.com/project/timonwong/pyastyle

This is a python wrapper extension for `Artistic Style`_, a wonderful code formatter & beautifier.


Install
-------

Install with ``pip`` using the command:

.. code-block:: bash

    $ pip install pyastyle

Or by cloning the repo from `GitHub <https://github.com/timonwong/pyastyle>`_:

.. code-block:: bash

    $ git clone git://github.com/timonwong/pyastyle.git

Then install it by running:

.. code-block:: bash

    $ python setup.py install


Upgrade
-------

You can upgrade your crypto version with the command:

.. code-block:: bash

    $ pip install --upgrade crypto


API
---

* ``pyastyle.version()``
* ``pyastyle.format(code, options)``


Credits
-------

**Artistic Style** - A Free, Fast and Small Automatic Formatter for C, C++, C#, and Java Source Code

Licensed under `GNU Lesser General Public License version 3.0`_

.. _Artistic Style: http://sourceforge.net/projects/astyle
.. _GNU Lesser General Public License version 3.0: http://astyle.sourceforge.net/license.html
