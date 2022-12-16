class UndergroundSystem:

    def __init__(self):
        self.startTimes = {}
        self.startStations = {}
        self.total_durations = {}
        self.counts = {}

    def check_in(self, customer_id: int, station_name: str, t: int) -> None:
        if customer_id not in self.startTimes:
            self.startTimes[customer_id] = t
            self.startStations[customer_id] = station_name

    def check_out(self, customer_id: int, station_name: str, t: int) -> None:
        if customer_id not in self.startTimes:
            return

        key = (self.startStations[customer_id], station_name)

        if key in self.total_durations:
            self.total_durations[key] += t - self.startTimes[customer_id]
            self.counts[key] += 1
        else:
            self.total_durations[key] = t - self.startTimes[customer_id]
            self.counts[key] = 1

        del self.startStations[customer_id], self.startTimes[customer_id]

    def get_average_time(self, start_station: str, end_station: str) -> float:
        return self.total_durations[(start_station, end_station)] / self.counts[(start_station, end_station)]


if __name__ == '__main__':
    obj = UndergroundSystem()
    obj.check_in(45, "Leyton", 3)
    obj.check_in(32, "Paradise", 8)
    obj.check_in(27, "Leyton", 10)
    obj.check_out(45, "Waterloo", 15)
    obj.check_out(27, "Waterloo", 20)
    obj.check_out(32, "Cambridge", 22)
    print(obj.get_average_time("Paradise", "Cambridge"))
    print(obj.get_average_time("Leyton", "Waterloo"))
    obj.check_in(10, "Leyton", 24)
    print(obj.get_average_time("Leyton", "Waterloo"))
    obj.check_out(10, "Waterloo", 38)
    print(obj.get_average_time("Leyton", "Waterloo"))
