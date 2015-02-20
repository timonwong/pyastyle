import re

import pyastyle


def test_version_is_string():
    ver = pyastyle.version()
    assert isinstance(ver, str)


def test_version_is_numberic_like():
    ver = pyastyle.version()
    assert re.match(r'^(\d+\.){2,}(\d+\w?)$', ver)
