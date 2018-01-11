def get_input():
    with open('input.txt') as file:
        men = file.readline().split()
        women = file.readline().split()
        n = len(men)
        m_name_to_index = {men[i]: i for i in range(n)}
        w_name_to_index = {women[i]: i for i in range(n)}
        M = [None for _ in range(n)]
        w_m_pref = [None for _ in range(n)]
        for i in range(n):
            line = file.readline().split()
            M[m_name_to_index[line[0]]] = [w_name_to_index[woman] for woman in line[1:]]
        for i in range(n):
            line = file.readline().split()
            w_index = w_name_to_index[line[0]]
            w_m_pref[w_index] = [None] * n
            for i in range(1, n + 1):
                w_m_pref[w_index][m_name_to_index[line[i]]] = i - 1
    return n, men, women, M, w_m_pref


def main():
    n, men, women, m_pref, w_m_pref = get_input()
    free_men = [i for i in range(n)]
    wife_of = [-1] * n
    husband_of = [-1] * n
    proposal_count = [0] * n
    while free_men:
        man_index = free_men[-1]
        if proposal_count[man_index] >= n:
            free_men.pop()
        woman_index = m_pref[man_index][proposal_count[man_index]]
        if husband_of[woman_index] == -1:
            free_men.pop()
            husband_of[woman_index] = man_index
            wife_of[man_index] = woman_index
        elif w_m_pref[woman_index][husband_of[woman_index]] > w_m_pref[woman_index][man_index]:
            free_men.pop()
            wife_of[husband_of[woman_index]] = -1
            free_men.append(husband_of[woman_index])
            husband_of[woman_index] = man_index
            wife_of[man_index] = woman_index
        proposal_count[man_index] += 1
    for i in range(n):
        print(men[i] + ' - ' + women[wife_of[i]])


def is_stable(wife_of, w_m_pref):
    n = len(wife_of)
    for man in range(n):
        for other_man in range(n):
            if w_m_pref[wife_of[man]][other_man] < w_m_pref[wife_of[man]][man] and w_m_pref[wife_of[other_man]][man] < \
                    w_m_pref[wife_of[other_man]][other_man]:
                return False
    return True


def foo(pre, i, n):
    if i == n:
        return pre
    for j in range(n):
        pass

def main2():
    with open('input.txt') as file:
        men = file.readline().split()
        women = file.readline().split()


if __name__ == '__main__':
    main()
