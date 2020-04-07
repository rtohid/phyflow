from __future__ import absolute_import
from collections import defaultdict

__license__ = """
Copyright (c) 2020 R. Tohid

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
"""


class DataRegistry:
    variables = defaultdict(lambda: None)

    def __init__(self, data, addr):
        self.data = data
        self.addr = addr
        self.update()

    def update(self):
        pass
