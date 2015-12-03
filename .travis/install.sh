#!/bin/bash

set -e
set -x

if [[ "$(uname -s)" == 'Darwin' ]]; then
    DARWIN=true
else
    DARWIN=false
fi

if [[ "$DARWIN" = true ]]; then
    brew update

    if which pyenv > /dev/null; then
        eval "$(pyenv init -)"
    fi

    case "${TOXENV}" in
        py26)
            brew upgrade pyenv
            pyenv install 2.6.6
            pyenv global 2.6.6
            ;;
        py27)
            curl -O https://bootstrap.pypa.io/get-pip.py
            sudo python get-pip.py
            ;;
        py32)
            brew upgrade pyenv
            pyenv install 3.2.5
            pyenv global 3.3.5
            ;;
        py33)
            brew upgrade pyenv
            pyenv install 3.3.6
            pyenv global 3.3.6
            ;;
        py34)
            brew upgrade pyenv
            pyenv install 3.4.2
            pyenv global 3.4.2
            ;;
        py35)
            brew upgrade pyenv
            pyenv install 3.5.0
            pyenv global 3.5.0
            ;;
    esac

    pyenv rehash

else
    sudo add-apt-repository -y ppa:fkrull/deadsnakes
    sudo apt-get -y update

    case "${TOXENV}" in
        py26)
            sudo apt-get install python2.6 python2.6-dev
            ;;
        py27)
            # Already shipped with ubuntu, skip
            ;;
        py32)
            sudo apt-get install python3.2 python3.2-dev
            ;;
        py33)
            sudo apt-get install python3.3 python3.3-dev
            ;;
        py34)
            sudo apt-get install python3.4 python3.4-dev
            ;;
        py35)
            sudo apt-get install python3.5 python3.5-dev
            ;;
    esac
fi

sudo pip install virtualenv
virtualenv ~/.venv
source ~/.venv/bin/activate
pip install tox
