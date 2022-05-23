from datetime import datetime as dt


def NumericTime(timeString: str, separator: str, conf: int,  offset: int = 0) -> int:
    try:
        time = timeString.split(separator)
        for i in range(3):
            time[i] = int(time[i])
        
        if conf == 0: # To Hours
            totalTime = time[0] # Adding Hours
            totalTime += time[1]/60 # Adding minutes
            totalTime += time[2]/3600 # Seconds to minutes
            totalTime += offset # Adding Offset
            return totalTime
            
        elif conf == 1: # To minutes
            totalTime = time[0]*60 # Hours to minutes
            totalTime += time[1] # Adding minutes
            totalTime += time[2]/60 # Seconds to minutes
            totalTime += offset # Adding Offset
            return totalTime
        
        elif conf == 2: # To seconds
            totalTime = time[0]*3600 # Hours to seconds
            totalTime += time[1]*60 # Adding minutes
            totalTime += time[2] # Seconds to minutes
            totalTime += offset # Adding Offset
            return totalTime
        
        else:
            return None
        
    except Exception as e:
        print(e)
        return None


now = dt.now()
nowstr = now.strftime("%H:%M:%S")

Hours = NumericTime(nowstr,":",0)
Minutes = NumericTime(nowstr,":",1)
Seconds = NumericTime(nowstr,":",2)


print(f"El string {nowstr}\nTiene:\n\n\t{Hours:.2f} Horas\n\t{Minutes:.2f} Minutos\n\t{Seconds:.2f} Segundos")