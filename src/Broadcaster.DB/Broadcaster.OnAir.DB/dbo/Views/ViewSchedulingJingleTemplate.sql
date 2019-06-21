
CREATE VIEW [dbo].[ViewSchedulingJingleTemplate]
AS
SELECT dbo.SchedulingTemplate.ID AS ID, 
    dbo.SchedulingTemplate.Name AS Name, 
    dbo.SchedulingTemplate.Category AS TypeID, 
    dbo.SchedulingTemplate.MinRythm AS MinRythm, 
    dbo.SchedulingTemplate.MaxRythm AS MaxRythm, 
    dbo.SchedulingTemplate.MinLen AS MinLen, 
    dbo.SchedulingTemplate.MaxLen AS MaxLen, 
    Broadcaster.dbo.TypeOfJingle.Name AS TypeName
FROM dbo.SchedulingTemplate LEFT OUTER JOIN
    Broadcaster.dbo.TypeOfJingle ON 
    dbo.SchedulingTemplate.Category = Broadcaster.dbo.TypeOfJingle.ID
WHERE (dbo.SchedulingTemplate.Type = 52)

