class UndergroundSystem:

    def __init__(self):
        self.customers = {}
        self.averages = {}

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        if id in self.customers:
            return

        self.customers[id] = {"startStationName": stationName, "startStationTime": t}

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        if id not in self.customers:
            return

        total_time = t - self.customers[id]["startStationTime"]
        concat_str = self.customers[id]["startStationName"] + "->" + stationName

        if concat_str in self.averages:
            self.averages[concat_str]["totalTime"] += total_time
            self.averages[concat_str]["totalOccurrences"] += 1
        else:
            self.averages[concat_str] = {"totalTime": total_time, "totalOccurrences": 1}

        del self.customers[id]

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        concat_str = startStation + "->" + endStation
        total_time = self.averages[concat_str]["totalTime"]
        total_occurrences = self.averages[concat_str]["totalOccurrences"]

        return total_time / total_occurrences


if __name__ == '__main__':
    obj = UndergroundSystem()
    obj.checkIn(45, "Leyton", 3)
    obj.checkIn(32, "Paradise", 8)
    obj.checkIn(27, "Leyton", 10)
    obj.checkOut(45, "Waterloo", 15)
    obj.checkOut(27, "Waterloo", 20)
    obj.checkOut(32, "Cambridge", 22)
    print(obj.getAverageTime("Paradise", "Cambridge"))
    print(obj.getAverageTime("Leyton", "Waterloo"))
    obj.checkIn(10, "Leyton", 24)
    print(obj.getAverageTime("Leyton", "Waterloo"))
    obj.checkOut(10, "Waterloo", 38)
    print(obj.getAverageTime("Leyton", "Waterloo"))


# Your UndergroundSystem object will be instantiated and called as such:
# obj = UndergroundSystem()
# obj.checkIn(id,stationName,t)
# obj.checkOut(id,stationName,t)
# param_3 = obj.getAverageTime(startStation,endStation)