import re

import pyastyle
import pytest


def test_version_is_string():
    ver = pyastyle.version()
    assert isinstance(ver, str)


def test_version_is_numberic_like():
    ver = pyastyle.version()
    assert re.match(r'^(\d+\.){2,}(\d+\w?)$', ver)


def test_format_simple_code():
    code = '''\
int main(void)
{
  }'''
    expected = '''\
int main(void)
{
}'''
    assert expected == pyastyle.format(code, '--style=allman')


def test_format_invalid_options():
    with pytest.raises(pyastyle.error) as exc:
        pyastyle.format('int main() {}', '--invalid-options-hereXXXXXX')
    assert '[130]' in str(exc)
