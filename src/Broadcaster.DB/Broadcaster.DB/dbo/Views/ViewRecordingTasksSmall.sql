
CREATE VIEW [dbo].[ViewRecordingTasksSmall]
AS
SELECT dbo.RecordingTask.ID, dbo.RecordingTask.Name, 
    dbo.RecordingTask.TalentID, dbo.RecordingTask.Completed, 
    dbo.OnAirUser.Name AS UserName
FROM dbo.OnAirUser INNER JOIN
    dbo.RecordingTask ON 
    dbo.OnAirUser.ID = dbo.RecordingTask.TalentID



