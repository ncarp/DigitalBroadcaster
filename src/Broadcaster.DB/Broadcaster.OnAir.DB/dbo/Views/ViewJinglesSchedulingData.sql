
CREATE VIEW [dbo].[ViewJinglesSchedulingData]
AS
SELECT ViewJingles_OnAir.*, 
    ViewJingleMaxScheduledDate.MaxDate AS MaxDate
FROM dbo.ViewJingles_OnAir LEFT OUTER JOIN
    dbo.ViewJingleMaxScheduledDate ON 
    dbo.ViewJingles_OnAir.JingleID = dbo.ViewJingleMaxScheduledDate.ItemID

