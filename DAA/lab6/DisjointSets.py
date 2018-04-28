class Node:
    def __init__(self, val):
        self.val = val
        self.parent = self
        self.rank = 0


class DisjointSets:
    def __init__(self):
        self.element_nodes = []

    def make_set(self, val):
        s = Node(val)
        self.element_nodes.append(s)
        return s

    def union(self, s1, s2):
        s1 = self.find_set(s1)
        s2 = self.find_set(s2)
        if s1 == s2:
            return False
        if s1.rank == s2.rank:
            s2.parent = s1
            s1.rank += 1
        elif s1.rank < s2.rank:
            s1.parent = s2
        else:
            s2.parent = s1
        return True

    def find_set(self, s):
        if s.parent == s:
            return s
        return self.find_set(s.parent)

    def __str__(self):
        sets = {}
        for node in self.element_nodes:
            key = str(self.find_set(node).val)
            if key in sets:
                sets[key].append(node.val)
            else:
                sets[key] = [node.val]
        ret = ''
        for key in sets:
            ret += str(sets[key]) + ', '
        return ret[:-2]


def main():
    sets = DisjointSets()
    s0 = sets.make_set(0)
    s1 = sets.make_set(1)
    s2 = sets.make_set(2)
    s3 = sets.make_set(3)
    s4 = sets.make_set(4)

    sets.union(s0, s2)
    sets.union(s0, s1)
    sets.union(s4, s3)

    print(sets)


if __name__ == '__main__':
    main()
