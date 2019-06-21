CREATE VIEW [dbo].[ViewRecordingTasks]
AS
SELECT     dbo.RecordingTask.ID, dbo.RecordingTask.Name, dbo.RecordingTask.TalentID, dbo.RecordingTask.Deadline, dbo.RecordingTask.Todo, 
                      dbo.RecordingTask.Completed, dbo.OnAirUser.Name AS UserName
FROM         dbo.RecordingTask INNER JOIN
                      dbo.OnAirUser ON dbo.RecordingTask.TalentID = dbo.OnAirUser.ID


