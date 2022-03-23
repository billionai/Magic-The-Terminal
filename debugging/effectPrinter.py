import gdb.printing

class effectPrettyPrinter:
    def __init__(self, val):
        self.val = val

    def to_string(self):
        s = str(self.val['name']) #remove [] from name
        s += ': ' + self.getResult(int(self.val['result']))
        if(self.val['cost'] != 1):
            s+= ' costing ' + str(self.val['cost']) + self.getCost(int(self.val['cost']))
        return s
        
    def getResult(self, res):
        returns = ['INVALID_RESULT',
                   'create mana',
                   'tap the target',
                   'deal damage',
                   'add a counter',
                   'add a temporary trait',
                   'add a temporary counter']
        if(res == 0):
            return 'INVALID_RESULT'
        ret = ''
        count = 0
        while(res):
            if(res % 2 == 1):
                if(ret):
                    ret+=' and '
                ret += returns[count]
            res = res // 2
            count += 1
        return ret

    def getCost(self, cost):
        returns = ['INVALID_COST',
                   'free',
                   'tap the card wit this effect',
                   'some mana',
                   'sacrifice a card']
        if (cost == 0):
            return 'INVALID_COST'
        ret = ''
        count = 0
        while(cost):
            if(cost % 2 == 1):
                if(ret):
                    ret+=' and '
                ret += returns[count]
            cost = cost // 2
            count += 1
        return ret

def effect_lookup_function(val):
    if(str(val.type) == 'Effect'):
        return effectPrettyPrinter(val)
    return None

gdb.pretty_printers.append(effect_lookup_function)
