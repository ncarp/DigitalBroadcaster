
CREATE VIEW [dbo].[ViewMaxMinYearOnSchedule]
AS
SELECT MIN(YEAR(Date)) AS [Min], MAX(YEAR(date)) 
    AS [Max]
FROM schedulingheadlines

