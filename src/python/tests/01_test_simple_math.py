import pytest
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))
from simple_math import *

def test_simple_math():
    assert 10 == add_vec(6, 4)
